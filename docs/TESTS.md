# Testes, resultados e limitações

Testes manuais em MH Rise/Sunbreak, Galaxy S25 SM-S931B, Android 17, Adreno 830. A sequência ocorreu em 14–17/10/2026. O jogador avaliou chão/iluminação no lobby e Wirebugs/insetos na primeira área da missão de Aknosom. Nem todas as comparações conservaram exatamente a câmera ou a temperatura; avaliações de fluidez são qualitativas, salvo medições indicadas.

| Teste | Resultado observado |
|---|---|
| Nightly, GPU Low/High | Brilho incorreto no chão; GPU alta não o resolveu. |
| Driver Qualcomm do sistema | Fechamento; SIGSEGV em VulkanWorker/vulkan.adreno.so e chamada indireta indexada. |
| Resolução 1,25× | Brilho pareceu menor, defeito permaneceu; câmeras diferentes impedem comparação quantitativa. |
| Phi em compute / múltiplas bases NVN | Ativação confirmada; brilho permaneceu. |
| FP16→FP32 | Conversão e validação SPIR-V confirmadas; brilho permaneceu. |
| Turnip V36 vs referências anteriores | Brilho permaneceu; não foi estabelecida vantagem geral de um pacote. |
| Conversão BCn | Ativação confirmada; brilho permaneceu. |
| Máscara constante do sampler | Chão normal e iluminação melhor, confirmado pelo usuário. A/B desligado trouxe de volta o brilho. |
| Phi de partículas junto ao sampler | Tela preta com HUD e crash; teste interrompido. Houve também assert de textura 3D/device loss; não provar causalidade exclusiva de phi. |
| NullTIC | Piscar igual. |
| Dumps/logs de rotina desligados | Sem melhora percebida de fluidez. |
| GPU Low original + sampler | Boa fluidez, insetos ausentes. |
| DMA seguro + sincronização precisa | Objetos presentes, lento/piscando. |
| DMA seguro isolado | Objetos presentes, lento/luzes piscando. |
| Sincronização precisa isolada | Objetos presentes, lento/piscando. |
| Refresh de macros em Low | Insetos ausentes; não houve confirmação de acionamento suficiente desse caminho. |
| Buffer+QueryCache, sem texturas | Objetos presentes, mais lento que Low simples. |
| QueryCache/contadores apenas | Insetos ausentes. |
| BufferCache apenas | Objetos presentes, fluidez inferior a Low simples. |
| NativeIndirect forçado | Regressão grave: cenário/personagens desapareceram. Removido; geometria recuperada ao restaurar modo anterior. |
| Barreira compute pós-dispatch | Acionou, insetos ausentes, desempenho normal. |
| FiveWordSync | Objetos presentes, desempenho diminuiu. |
| Prefetch 64 KiB limitado ao buffer | Ativou; nenhum ganho percebido. |
| RefreshedDraw após ler cinco words | Objetos presentes, desempenho ruim. Ramo posteriormente removido. |
| A/B ao vivo de FiveWordSync | Mesma cena/câmera: on 27,47/27,79 FPS; off 29,82/30,01 FPS. Captura on mostra Wirebug; off não. Não mede frequência de flicker por si só. |
| PendingWrites | Proteção acionou; insetos continuaram ausentes, desempenho melhor. |
| Diagnóstico de parâmetros | Marca dirty presente em e3a/e42; estimativa de índices zero em amostras. Instância CPU zero não significa instância GPU zero. |
| **IndexBound + sampler, Low/DMA/fence padrão** | **Usuário confirmou insetos presentes sem piscar e fluidez melhor. Referência aprovada.** |
| AppletRing posterior | Usuário percebeu desempenho semelhante. Sem ganho confirmado; aparelho estava termicamente limitado durante a investigação posterior. |
| Resolução 0,75× / shaders assíncronos | Sugeridos como testes posteriores; **não aplicados nem validados** nesta sessão. |

## Evidência técnica

- Macro e3a: hash `0217920100488ff7`, HLE indexed extended. e42: `3f5e74b9c9a50164`, HLE multidraw indirect count.
- Readback de cinco words alterou, por exemplo, instance count de zero para valor positivo; transferir esses dados sincronicamente recuperava objetos com custo.
- IndexBound acionou aos 49,476876 s: 2432 índices, 4864 bytes contínuos, limite registrado 1009082897151 bytes. A proteção por layout/continuidade evita confiar nesse limite amplo.
- SPIR-V: 420 shaders iniciais, 423 no teste phi, 430 no FP32 e 433 na etapa sampler passaram nas respectivas validações estruturais. Isso não prova semântica visual correta nem valida todos os caminhos possíveis.
- Teste sintético ARM64 de PendingWrites, com RangeSet/OverlapRangeSet reais, passou em casos de escrita pendente, snapshots acumulados, invalidação CPU e intervalos disjuntos. A aprovação sintética não se traduziu em recuperação dos insetos.
- Builds experimentais compilaram; verificações `git diff --check` e aplicação/reversão de patches foram usadas nas etapas registradas.

## Medições de desempenho

O A/B FiveWordSync analisou janelas efetivas de cerca de 4,0–4,4 s por amostra, limitadas pelo histórico do SurfaceFlinger. Diferença média de cerca de 2,3 FPS/~8% nessa cena. Transições de controle foram confirmadas no log do próprio processo.

Na referência IndexBound, uma amostra posterior do **lobby**, com 119 timestamps em aproximadamente 3,93 s, mediu 30,0048 FPS, mediana 33,3284 ms, p90 33,3343 ms e máximo 58,3243 ms. Não comparar isso diretamente ao A/B do mapa como se fosse um ganho medido em condições equivalentes.

Perfis simpleperf com `trace-offcpu` incluem esperas e não indicam diretamente utilização da CPU. Perfis anteriores tinham muitas callchains incompletas. Na referência posterior foram preservados 126243 samples/zero perdas, biblioteca correspondente e relatórios. Eles mostraram esperas na captura applet/apresentação e sincronização, sem isolar tempo puro de GPU.

Após uso prolongado, HAL indicou SKIN perto de 45 °C e Thermal Status 3 (severe), com bateria próxima de 44–45 °C. Isso sustenta investigar temperatura, mas não prova que toda queda tenha essa causa. Nenhuma proteção térmica foi desativada e nenhum root foi feito.

Não foi demonstrado ganho sustentado de FPS em todas as missões, estabilidade por horas, compatibilidade OpenGL ou equivalência entre drivers. A validação final é o relato do jogador na cena testada, com evidência de ativação da correção.
