# Alterações técnicas — 14–17/10/2026

Base fixa: `14da4482a4668928bad43bb67ef12f96b9c9d972`. A referência validada contém 19 arquivos modificados. O estado posterior modifica também `renderer_vulkan.cpp`, totalizando 20. Os patches completos, e não apenas este resumo, registram as diferenças exatas.

A release do APK retorna à referência gráfica sem AppletRing e acrescenta quatro arquivos: `src/android/app/build.gradle.kts` remove o sufixo visível Debug Release e desativa a depuração Android/JNI; `src/common/settings.h` define 16392 como valor padrão das flags; `CMakeLists.txt` remapeia caminhos locais do código e NDK na compilação Android com `-ffile-prefix-map`. `externals/CMakeLists.txt` preserva esse remapeamento no cubeb, que limpa as opções herdadas. São 23 arquivos modificados na release. Consulte `release-mhrise-full.patch` e [RELEASE.md](RELEASE.md). Não houve novo teste manual em missão desse arquivo binário.

## Correções ativas na referência

### Máscara constante de sampler — bit 8

No shader observado com identificador `09f92bcb238910c0`, um OR com `0x10500000` modifica os bits superiores do handle de textura. O rastreador anterior reconhecia combinações de duas origens de constant buffer, mas perdia a parcela constante desse padrão. A alteração preserva a máscara dos 12 bits superiores, inclui-a nas chaves e na deduplicação e aplica a mesma informação na seleção dos samplers Vulkan/OpenGL, em gráficos e compute.

O teste A/B com a mesma build, habilitando/desabilitando somente essa correção, recuperou/reintroduziu o brilho incorreto. O usuário confirmou melhora da iluminação global. Luzes piscavam em ambos os modos antes da correção final de índices; não foram atribuídas à máscara sem evidência.

### Buffer de índices indiretos — bit 16384

`EstimateIndexBufferSize()` usa uma estimativa derivada de buffers de vértices. Em desenhos observados, ela retornava zero, levando `UpdateIndexBuffer()` a selecionar `NULL_BINDING`. Quando esse limite é zero e o intervalo de índices registrado é positivo, a correção usa o menor limite entre o intervalo registrado, `UINT32_MAX`, o layout disponível e a faixa realmente contínua em `MaxContinuousRange()`, convertendo bytes em índices.

Ativação real: **2432 índices / 4864 bytes contínuos**, com um limite registrado muito maior. Os clamps são essenciais. Não houve readback síncrono adicional nem mudança para precisão GPU alta. Vertex pulling é uma hipótese para a estimativa de vértices zero, não uma causa demonstrada para cada draw.

O bit 16384 foi reutilizado: anteriormente significava RefreshedDraw. Esse ramo anterior foi removido da referência. Não reaplique configurações de APKs antigos apenas pelo valor numérico.

## Inventário por arquivo

| Arquivo sob `src/` | Alteração |
|---|---|
| `shader_recompiler/environment.h` | Máscara constante em identificadores/chaves de recursos e suporte ao rastreamento. |
| `shader_recompiler/ir_opt/texture_pass.cpp` | Preservação do OR constante do sampler, propagação/deduplicação e proteção contra ciclos de rastreamento. |
| `shader_recompiler/shader_info.h` | Metadados da máscara de sampler em descritores. |
| `video_core/renderer_vulkan/vk_graphics_pipeline.cpp` | Aplicação da máscara no binding de samplers gráficos e diagnóstico limitado. |
| `video_core/renderer_vulkan/vk_compute_pipeline.cpp` | Mesma máscara no binding compute. |
| `video_core/renderer_opengl/gl_graphics_pipeline.cpp` | Propagação equivalente no caminho gráfico OpenGL; sem validação visual OpenGL no S25. |
| `video_core/renderer_opengl/gl_compute_pipeline.cpp` | Propagação equivalente no caminho compute OpenGL; não validado no S25. |
| `video_core/engines/maxwell_3d.cpp` | Correção IndexBound, diagnóstico limitado de macros e antigo experimento de refresh condicionado. |
| `video_core/macro.cpp` | Mapeamento de macros HLE e contadores de instâncias/dirty para diagnóstico. O experimento NativeIndirect que causou regressão foi removido. |
| `video_core/dma_pusher.cpp` | Experimentos de sincronização seletiva de Buffer/QueryCache, segmentos de cinco words, diagnóstico e controle local limitado para A/B. Desligados na referência. |
| `video_core/buffer_cache/buffer_cache.h` | Prefetch limitado ao buffer e preservação de escritas pendentes ao retirar download antigo. Desligados na referência. |
| `video_core/renderer_vulkan/vk_rasterizer.cpp` | Barreira compute experimental, desligada na referência. |
| `video_core/shader_environment.cpp` | Tratamento experimental de consultas TIC fora da tabela, desligado na referência. |
| `video_core/vulkan_common/vulkan_device.cpp` | Teste para desativar BCn nativo e usar conversão, desligado na referência. |
| `video_core/renderer_vulkan/vk_pipeline_cache.cpp` | Dumps de IR antes/depois dos passes de recursos e teste FP16→FP32. Dumps/experimento FP32 desligados na referência. |
| `shader_recompiler/frontend/maxwell/translate_program.cpp` | Exportação opcional de IR anterior aos passes de recursos. |
| `shader_recompiler/frontend/maxwell/translate_program.h` | Interface correspondente do diagnóstico de IR. |
| `shader_recompiler/ir_opt/global_memory_to_storage_buffer_pass.cpp` | Hipótese phi/múltiplas bases NVN para preservar loads globais, condicionada ao bit 1 e desligada na referência. |
| `shader_recompiler/backend/spirv/spirv_emit_context.cpp` | Ajuste do fallback de descritores SSBO: slots compactados não são os índices de bits NVN. Presente no snapshot; não demonstrado como correção isolada do MH Rise. |
| `video_core/renderer_vulkan/renderer_vulkan.cpp` | **Apenas na variante posterior:** três conjuntos alternados de recursos da captura applet em vez de um. Sem ganho perceptível confirmado. |

## Flags no snapshot validado

| Bit | Função no snapshot | Estado em 16392 |
|---|---|---|
| 1 | Hipótese phi / loads globais | Desligado |
| 2 | Conversão FP16→FP32 | Desligado |
| 4 | Conversão BCn | Desligado |
| 8 | Máscara constante de sampler | **Ligado** |
| 16 | NullTIC | Desligado |
| 32 | Refresh de parâmetros em Low | Desligado |
| 64 | Buffer+QueryCache para comandos | Desligado |
| 128 | QueryCache apenas | Desligado |
| 256 | BufferCache apenas | Desligado |
| 512 | Diagnóstico de macros/readbacks | Desligado |
| 1024 | PendingWrites; não o antigo NativeIndirect | Desligado |
| 2048 | ComputeVisibility | Desligado |
| 4096 | FiveWordSync | Desligado |
| 8192 | ParameterPrefetch, depende de 4096 | Desligado |
| 16384 | IndexBound; não o antigo RefreshedDraw | **Ligado** |
| 32768 | Controle de A/B de FiveWordSync | Desligado |

`debug_knobs` é `u16`; uma tentativa de usar 65536 foi truncada e corrigida antes da coleta útil. Essas flags são ferramentas de investigação, não uma interface estável.

## Artefatos e limites

O patch completo da referência mantém ramos de investigação desligados. O pacote não é um backport mínimo revisado pelo upstream. Os dois patches isolados ajudam a examinar as correções, mas não representam sozinhos todo o código contido no APK validado. Patches antigos do arquivo histórico incluem versões de código depois removidas; consulte [TESTS.md](TESTS.md) antes de reutilizá-los.
