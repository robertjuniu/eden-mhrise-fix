# Eden — fix experimental específico para Monster Hunter Rise

Documentação e patches de uma investigação independente de brilho incorreto e objetos ausentes em **Monster Hunter Rise / Sunbreak**, usando Eden no Galaxy S25. Alterações e testes realizados em 14–17 de outubro de 2026.

**Eden não é um projeto deste repositório nem de seu mantenedor.** É software livre do Eden Emulator Project, iniciado por Camille LaVey, com contribuições e código herdado dos projetos citados em [CREDITS.md](CREDITS.md). Este material não é uma versão oficial, não tem aprovação declarada dos desenvolvedores e não representa o projeto Eden.

## Resultado validado

O jogador confirmou iluminação corrigida, insetos/Wirebugs presentes sem piscar e melhor fluidez no mapa testado, mantendo precisão GPU baixa. Duas correções estão ativas:

1. Preservação dos bits constantes do sampler nos identificadores de textura e nos bindings.
2. Limite válido do buffer de índices indiretos quando a estimativa baseada em vértices retorna zero.

A validação é específica para MH Rise no dispositivo e nas cenas descritos. Não há garantia de compatibilidade com outros jogos, drivers ou aparelhos. Os ramos de código não verificam o ID do jogo; por isso, não devem ser tratados como ajustes globais recomendados para todos os títulos.

## Referência

| Item | Valor |
|---|---|
| Upstream | [eden-emu/eden](https://git.eden-emu.dev/eden-emu/eden) |
| Commit base | `14da4482a4668928bad43bb67ef12f96b9c9d972` |
| Aparelho testado | Samsung Galaxy S25 SM-S931B, Android 17, Adreno 830 |
| Jogo observado | Monster Hunter Rise / Sunbreak, conteúdo identificado como v16.0.2 |
| Driver observado na referência final | Turnip, Vulkan 1.4.359; o overlay também mostra 23.0.0 |
| APK local validado | `Eden_MHRISEFIX.apk` |
| SHA-256 do APK validado | `33e52ee029abe1cb4c1baf9ae7a1f01dd62c9cd3add168dc9e957a920c2a19ce` |
| Variante Android | `MainlineRelWithDebInfo` |
| Pacote | `dev.eden.eden_emulator.relWithDebInfo` |
| Flags experimentais validadas | `debug_knobs=16392` = sampler 8 + índice 16384 |

O nome V36/V37 variou durante os testes; não se deve inferir o driver ativo de um nome antigo de arquivo. Os resultados iniciais não são uma certificação de todos os drivers Turnip.

## Conteúdo

- [Alterações por arquivo](docs/CHANGES.md), [testes e resultados](docs/TESTS.md) e [build](docs/BUILD.md).
- `patches/validated-mhrise-full.patch`: diferenças completas correspondentes à referência validada, inclusive experimentos desligados.
- `patches/current-experiments-full.patch`: estado posterior, com o teste de recursos alternados da captura interna. **Não substitui a referência validada.**
- Patches isolados das duas correções e do teste de captura; hipóteses anteriores em `patches/archive/`.
- [Configuração mínima documentada](config/mhrise-reference.ini), sem caminhos, contas ou identificadores particulares do telefone.

Os patches completos são alternativas aplicadas sobre o commit base. Não aplique ambos em sequência. Patches arquivados representam diferentes momentos da investigação e podem sobrepor alterações; não são uma série cumulativa para instalação.

## Software livre, créditos e IA

O Eden declara licença **GNU GPL versão 3 ou posterior**. Os patches derivados são disponibilizados sob os mesmos termos; os avisos e licenças dos arquivos originais permanecem aplicáveis. Consulte [LICENSE.txt](LICENSE.txt), [CREDITS.md](CREDITS.md) e [PUBLICATION.md](docs/PUBLICATION.md).

Esta investigação, suas alterações de código e esta documentação tiveram assistência substancial de **OpenAI Codex**. O jogador executou e avaliou testes visuais no próprio aparelho; isso não equivale a revisão humana completa de cada linha. Não alegamos revisão ou aceitação pelo upstream. Nenhuma assinatura de desenvolvedor humano foi criada automaticamente.

Este repositório distribui documentação e patches, **sem APKs, jogos, firmware, chaves de console, saves ou dumps de shaders do jogo**. O hash acima identifica o artefato local testado. Antes de distribuir um APK, é necessário disponibilizar seu código-fonte correspondente completo e as instruções/dependências de build exigidas pela GPL; um link para a versão atual do Eden ou somente os dois patches isolados não basta como substituto desse cuidado.

## Desempenho

A referência atingiu aproximadamente 30 FPS numa amostra curta do lobby. Isso não mede uma luta pesada nem garante 30 FPS sustentados. Após testes prolongados, o Android reportou limitação térmica severa; a variante posterior de captura não teve ganho perceptível confirmado. Consulte as limitações em [TESTS.md](docs/TESTS.md).

Para suporte oficial e downloads oficiais, use os canais do [Eden](https://eden-emu.dev). Resultados desta modificação devem ser identificados como provenientes de uma build não oficial.
