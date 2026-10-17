# Eden — fix experimental específico para Monster Hunter Rise

Documentação e patches de uma investigação independente de brilho incorreto e objetos ausentes em **Monster Hunter Rise / Sunbreak**, usando Eden. Os testes foram realizados no Galaxy S25. Alterações e testes realizados em 14–17 de outubro de 2026.

**APK:** [baixar Eden_MHRISEFIX.apk](https://github.com/robertjuniu/eden-mhrise-fix/releases/download/mhrise-fix-2026.10.17/Eden_MHRISEFIX.apk). Consulte a [release](https://github.com/robertjuniu/eden-mhrise-fix/releases/tag/mhrise-fix-2026.10.17) para fontes correspondentes, licenças e hashes; veja [RELEASE.md](docs/RELEASE.md) para instalação e limitações. O nome visível no Android é **Eden**.

**Eden não é um projeto deste repositório nem de seu mantenedor.** É software livre do Eden Emulator Project, iniciado por Camille LaVey, com contribuições e código herdado dos projetos citados em [CREDITS.md](CREDITS.md). Este material não é uma versão oficial, não tem aprovação declarada dos desenvolvedores e não representa o projeto Eden.

## Resultado validado

O jogador confirmou iluminação corrigida, insetos/Wirebugs presentes e melhor fluidez no mapa testado, mantendo precisão GPU baixa. Em avaliação posterior, relatou que os insetos ainda piscam, mas com menor frequência; o piscar não foi completamente corrigido. Duas correções estão ativas:

1. Preservação dos bits constantes do sampler nos identificadores de textura e nos bindings.
2. Limite válido do buffer de índices indiretos quando a estimativa baseada em vértices retorna zero.

A validação é específica para MH Rise no dispositivo e nas cenas descritos. Não há garantia de compatibilidade com outros jogos, drivers ou aparelhos. Os ramos de código não verificam o ID do jogo; por isso, não devem ser tratados como ajustes globais recomendados para todos os títulos.

## Proporção de tela 19,5:9

A versão atual acrescenta **19,5:9**, selecionável nas configurações gráficas globais ou por jogo. A opção redimensiona a imagem final e pode ser usada em outros jogos e aparelhos; não amplia o campo de visão nativo. Interfaces podem ficar mais largas, e vídeos com barras internas podem mantê-las. Apenas MH Rise foi testado nesta etapa.

Os testes foram feitos no Galaxy S25: o jogador confirmou o funcionamento da proporção no MH Rise, e uma captura do menu de missões mostrou preenchimento de 2340 × 1080. Em instalações novas, selecione **19.5:9** em **Proporção de tela**; o padrão 16:9 foi preservado.

O APK usa o pacote separado `dev.eden.eden_emulator.mhrise.screen`: instala ao lado da versão anterior e não importa seus dados automaticamente. O nome é **Eden**, a versão é `14da448-mhrise-screen`, e a depuração Android/JNI permanece desativada. Veja [instalação e verificações](docs/RELEASE.md).

## Referência

| Item | Valor |
|---|---|
| Upstream | [eden-emu/eden](https://git.eden-emu.dev/eden-emu/eden) |
| Commit base | `14da4482a4668928bad43bb67ef12f96b9c9d972` |
| Aparelho testado | Samsung Galaxy S25 SM-S931B, Android 17, Adreno 830 |
| Jogo observado | Monster Hunter Rise / Sunbreak, conteúdo identificado como v16.0.2 |
| Driver observado na referência final | Turnip, Vulkan 1.4.359; o overlay também mostra 23.0.0 |
| APK atual validado | `Eden_MHRISEFIX.apk` |
| SHA-256 do APK atual | `953693bc2cf1f75694a76ae0526ea7d8b6a3d8c772ebdd757d3c3d0c9d8fc127` |
| Variante Android | `MainlineRelWithDebInfo` |
| Pacote | `dev.eden.eden_emulator.mhrise.screen` |
| Flags experimentais validadas | `debug_knobs=16392` = sampler 8 + índice 16384 |

O nome V36/V37 variou durante os testes; não se deve inferir o driver ativo de um nome antigo de arquivo. Os resultados iniciais não são uma certificação de todos os drivers Turnip.

## Conteúdo

- [Alterações por arquivo](docs/CHANGES.md), [testes e resultados](docs/TESTS.md) e [build](docs/BUILD.md).
- `patches/validated-mhrise-full.patch`: diferenças completas correspondentes à referência validada, inclusive experimentos desligados.
- `patches/current-experiments-full.patch`: estado posterior, com o teste de recursos alternados da captura interna. **Não substitui a referência validada.**
- `patches/screen-19.5-9.patch`: alterações da proporção e instalação separada sobre as fontes da release anterior; o patch completo atual é `release-mhrise-full.patch`.
- Patches isolados das duas correções e do teste de captura; hipóteses anteriores em `patches/archive/`.
- [Configuração mínima documentada](config/mhrise-reference.ini), sem caminhos, contas ou identificadores particulares do telefone.

Os patches completos são alternativas aplicadas sobre o commit base. Não aplique ambos em sequência. Patches arquivados representam diferentes momentos da investigação e podem sobrepor alterações; não são uma série cumulativa para instalação.

## Software livre, créditos e IA

O Eden declara licença **GNU GPL versão 3 ou posterior**. Os patches derivados são disponibilizados sob os mesmos termos; os avisos e licenças dos arquivos originais permanecem aplicáveis. Consulte [LICENSE.txt](LICENSE.txt), [CREDITS.md](CREDITS.md) e [PUBLICATION.md](docs/PUBLICATION.md).

Esta investigação, suas alterações de código e esta documentação tiveram assistência substancial de **OpenAI Codex**. O jogador executou e avaliou testes visuais no próprio aparelho; isso não equivale a revisão humana completa de cada linha. Não alegamos revisão ou aceitação pelo upstream. Nenhuma assinatura de desenvolvedor humano foi criada automaticamente.

O repositório contém documentação e patches; a release experimental fornece o APK **junto de três pacotes de fontes/dependências**, scripts, licenças e hashes. Não são distribuídos jogos, firmware, chaves de console, saves ou dumps de shaders do jogo. O hash da tabela identifica o APK atual com a proporção 19,5:9 e as duas correções ativas por padrão. As diferenças e validações estão em [RELEASE.md](docs/RELEASE.md).

## Desempenho

A referência atingiu aproximadamente 30 FPS numa amostra curta do lobby. Isso não mede uma luta pesada nem garante 30 FPS sustentados. Após testes prolongados, o Android reportou limitação térmica severa; a variante posterior de captura não teve ganho perceptível confirmado. Consulte as limitações em [TESTS.md](docs/TESTS.md).

## Saves Steam → Switch

Consulte [SAVE-CONVERSION.md](docs/SAVE-CONVERSION.md): recomendação da versão [hashcade/mhrise-save-converter](https://github.com/hashcade/mhrise-save-converter), com créditos ao autor original **Jing Haihan** e à pesquisa **kvasszn/ree-save-editor**. No teste do jogador, Steam → Switch funcionou mantendo apenas o slot 1 na cópia usada para converter e removendo os slots 2/3. É um relato específico, não uma exigência universal; mantenha backups dos saves originais.

Para suporte oficial e downloads oficiais, use os canais do [Eden](https://eden-emu.dev). Resultados desta modificação devem ser identificados como provenientes de uma build não oficial.
