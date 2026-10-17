# APK experimental — Eden MH Rise Fix

[Release e downloads](https://github.com/robertjuniu/eden-mhrise-fix/releases/tag/mhrise-fix-2026.10.17)

Esta é uma distribuição **não oficial**, específica para a investigação de Monster Hunter Rise/Sunbreak. Eden é software do Eden Emulator Project e respectivos contribuidores, não do mantenedor deste fix. Créditos, GPL-3.0-or-later e declaração de assistência substancial de IA permanecem em README, CREDITS e NOTICE.

## APK

- Arquivo: `Eden_MHRISEFIX.apk`.
- Nome visível: **Eden**, sem “Debug Release”.
- Arquitetura: ARM64; Android 13/API 33 ou superior.
- Pacote: `dev.eden.eden_emulator.relWithDebInfo`.
- Versão: `14da448-mhrise-fix`; versionCode `34066238`.
- **Não depurável:** depuração Android e JNI desativadas. O nome interno da tarefa permanece `MainlineRelWithDebInfo`; pacote e assinatura foram preservados para atualização compatível sobre a build anterior. A assinatura continua sendo a de desenvolvimento, e a distribuição continua não oficial.
- SHA-256: `959a1782d106d265b64fabd0eedb2a50cf0f6f2742a8f236161aa4d95190b12d`.

As duas correções da referência validada foram mantidas: máscara constante do sampler e limite de índices indiretos. O experimento posterior AppletRing não está nesta release. O valor padrão de `debug_knobs` é 16392, habilitando os fixes em instalações novas; configurações antigas explícitas podem prevalecer. Use GPU baixa, DMA/fences padrão e modo portátil como na referência. Caminhos locais do código e do NDK são remapeados na compilação Android com `-ffile-prefix-map`; o relatório de dependências também foi higienizado.

A referência anterior foi testada no mapa pelo jogador, que confirmou insetos presentes sem piscar, brilho corrigido e melhor fluidez. Esta recompilação desativa a depuração Android/JNI, remapeia caminhos locais e passou no build, conferência do manifest, verificação de assinatura e busca limitada por identificadores particulares, mas **não recebeu um novo teste manual em missão**. O hash anterior 33e52e... identifica outro arquivo, preservado no histórico. Não há garantia para outros jogos/aparelhos nem promessa de FPS sustentado.

## Fontes correspondentes e licenças

Baixe os três pacotes da mesma release:

1. `Eden_MHRISEFIX-source.zip`: árvore completa do Eden no commit base `14da4482a4668928bad43bb67ef12f96b9c9d972`, já modificada com `patches/release-mhrise-full.patch`, incluindo scripts de build, documentação e avisos upstream.
2. `Eden_MHRISEFIX-native-dependencies.zip`: entradas CPM da compilação, fontes de dependências, arquivos-fonte dos fornecedores de bibliotecas pré-compiladas e seus scripts/licenças. Inclui o patch FFmpeg e sua proveniência.
3. `Eden_MHRISEFIX-android-dependencies.zip`: sources.jar e POMs das dependências Maven de runtime, grafo de dependências e manifest de downloads. As quatro BOMs são metadados, sem código Java/Kotlin próprio.

Os arquivos nativos originais em cache são incluídos como entradas de reprodução, **junto das suas fontes**; não confunda as bibliotecas `.a` com código-fonte. Os arquivos de fonte de fornecedores ficam em `third_party/source_archives`; as bibliotecas CPM construídas a partir de fonte ficam em `eden/.cache/cpm`. Os avisos/licenças específicos dessas dependências permanecem aplicáveis e acompanham seus diretórios/arquivos.

`SHA256SUMS.txt` e `release-manifest.json` identificam os artefatos. A distribuição não depende apenas do master atual do upstream nem apenas dos dois patches isolados.

## Reconstrução

Extraia os pacotes source e native-dependencies no mesmo diretório; a árvore resultante é `eden/`. Ela já contém as alterações; **não reaplique o patch**. Consulte `BUILD.md` e o arquivo `third_party/BUILD-SOURCES.md` dos pacotes de dependências.

Instale Java 21, Android SDK 36, NDK 28.2.13676358 e CMake 3.31.6. Use os scripts/wrapper da árvore. Se não houver `src/android/app/debug.keystore`, gere sua própria chave de desenvolvimento, sem publicar a chave:

```sh
keytool -genkeypair -keystore src/android/app/debug.keystore -alias androiddebugkey -storepass android -keypass android -dname "CN=Android Debug,O=Android,C=US" -keyalg RSA -keysize 2048 -validity 10000
```

Depois execute a tarefa `:app:assembleMainlineRelWithDebInfo` em `src/android` conforme BUILD.md. O Gradle obtém ferramentas e dependências de seus repositórios oficiais; os sources.jar/POMs fornecidos permitem consultar/modificar essas dependências. SDK/NDK/JDK/Gradle são ferramentas padrão externas, não estão incorporados como toolchains nos pacotes.

Ao recompilar fornecedores nativos, use os scripts e revisões documentados nos arquivos; o patch `ffmpeg-steamdeck.patch` incluído pode substituir a URL raw externa nos scripts FFmpeg. O identificador embutido `adbaa35` é o commit `adbaa353e295c5039b0f246ce81047486f597386` dos scripts `crueter-ci/FFmpeg`; o código FFmpeg é `946fcce07b6dcd0331c8cc609192aeff5e1924f8`. Essa correspondência foi conferida, e o patch foi validado com `git apply --check`.

Não se promete reprodução byte a byte: metadados e a sua assinatura mudam o hash. Instalar sobre outro APK exige pacote/assinatura compatíveis. Preserve backups; não desinstale uma instalação com dados importantes sem protegê-los.

## Saves Steam → Switch

Veja [SAVE-CONVERSION.md](SAVE-CONVERSION.md), com recomendação do conversor hashcade e créditos ao autor original Jing Haihan e à pesquisa kvasszn. No caso relatado, a conversão funcionou mantendo apenas o slot 1 numa cópia dos saves; não é regra universal nem instrução para apagar o save original.
