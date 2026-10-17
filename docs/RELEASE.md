# APK experimental — Eden MH Rise Fix

[Release e downloads](https://github.com/robertjuniu/eden-mhrise-fix/releases/tag/mhrise-fix-2026.10.17)

Distribuição não oficial com correções gráficas investigadas para Monster Hunter Rise/Sunbreak e uma opção geral de proporção 19,5:9. Os testes foram realizados no Galaxy S25. Eden pertence ao Eden Emulator Project e aos respectivos contribuidores; créditos, GPL-3.0-or-later e avisos de assistência de IA permanecem nos arquivos do projeto.

## APK e instalação

- Arquivo: `Eden_MHRISEFIX.apk`; nome visível **Eden**.
- ARM64, Android 13/API 33 ou superior.
- Pacote: `dev.eden.eden_emulator.mhrise.screen`.
- Versão: `14da448-mhrise-screen`; versionCode `34066836`.
- Depuração Android e JNI desativadas; assinatura anterior preservada.
- SHA-256: `953693bc2cf1f75694a76ae0526ea7d8b6a3d8c772ebdd757d3c3d0c9d8fc127`.

**Mudança de pacote:** este APK instala ao lado das versões antigas `.relWithDebInfo`/nightly; não as atualiza nem migra seus dados automaticamente. Configure a nova instalação e, se desejar, use os recursos de exportação/importação do aplicativo com uma cópia dos seus dados. Mantenha a instalação antiga e seus shaders até conferir a nova. Jogos, firmware, keys de console e saves não são distribuídos aqui.

Em **Configurações gráficas → Proporção de tela**, escolha **19.5:9** globalmente ou por jogo. O padrão 16:9 continua disponível. A opção redimensiona a imagem final, sem ampliar o campo de visão nativo; interfaces e vídeos podem ter resultados diferentes, incluindo barras internas. A opção pode ser usada em outros jogos e aparelhos, mas apenas MH Rise foi testado nesta etapa.

As correções de sampler e índices indiretos permanecem ativas por padrão (`debug_knobs=16392`). A referência usa GPU baixa, DMA/fences padrão e modo portátil; configurações antigas explícitas podem prevalecer. AppletRing não está incluído. Os insetos ainda podem piscar, com menor frequência conforme relato do jogador; não houve correção completa desse problema.

## Testes e verificações

O jogador confirmou o funcionamento de 19,5:9 no MH Rise. Uma captura do menu de missões preencheu 2340 × 1080. A compilação completa, lintVital, assinatura e manifest passaram nas verificações. Nome e versão visíveis não contêm Debug/relWithDebInfo. Isso não representa teste de todos os jogos ou garantia de FPS sustentado.

A revisão limitada da alteração de proporção não encontrou novas permissões Android nem novos componentes exportados. Foi repetida a busca nos artefatos e nos arquivos públicos por identificadores particulares conhecidos, caminhos locais e arquivos de chaves. Caminhos de compilação são remapeados com `-ffile-prefix-map`. Os resultados e hashes correspondem aos arquivos desta release; isso não equivale a auditoria completa, pentest ou garantia de ausência de vulnerabilidades. Bibliotecas e dependências existentes do Eden continuam fazendo parte da distribuição.

## Fontes correspondentes e licenças

- `Eden_MHRISEFIX-source.zip`: árvore completa já modificada, base `14da4482a4668928bad43bb67ef12f96b9c9d972`, scripts, documentação, licenças e avisos upstream.
- `Eden_MHRISEFIX-native-dependencies.zip`: entradas CPM e fontes/scripts/licenças dos fornecedores nativos, incluindo patch e proveniência FFmpeg.
- `Eden_MHRISEFIX-android-dependencies.zip`: fontes/POMs Maven, grafo de runtime e manifest de downloads. As quatro BOMs contêm metadados, sem código Java/Kotlin próprio.

Os pacotes de dependências não mudaram nesta atualização. Bibliotecas pré-compiladas são acompanhadas de suas fontes e scripts; avisos/licenças dos fornecedores permanecem aplicáveis. Confira `SHA256SUMS.txt` e `release-manifest.json`.

## Reconstrução

Extraia source e native-dependencies no mesmo diretório; a árvore `eden/` já está modificada, então não reaplique patches. Use Java 21, Android SDK 36, NDK 28.2.13676358 e CMake 3.31.6. Em `src/android`, execute `:app:assembleMainlineRelWithDebInfo -PedenStandaloneScreen=true` pelo wrapper Gradle. O nome interno da tarefa não torna o APK depurável.

Consulte [BUILD.md](BUILD.md) e `third_party/BUILD-SOURCES.md` nos pacotes de dependências. Gere sua própria chave de desenvolvimento se necessário; nenhuma chave particular de assinatura é distribuída. Ferramentas padrão SDK/NDK/JDK/Gradle são externas. Não se promete reprodução binária byte a byte: assinatura e metadados mudam o hash.

## Saves Steam → Switch

Veja [SAVE-CONVERSION.md](SAVE-CONVERSION.md), com recomendação de hashcade/mhrise-save-converter e créditos ao autor original Jing Haihan e à pesquisa kvasszn. O relato do slot 1 descreve um caso em uma cópia dos saves, não uma regra universal para apagar dados originais.
