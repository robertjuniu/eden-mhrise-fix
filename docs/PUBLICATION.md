# Licença, publicação e relação com o Eden

Revisão feita em 17/10/2026 sobre os documentos do commit base `14da4482a4668928bad43bb67ef12f96b9c9d972`.

## O que a licença permite

O README upstream declara **GPLv3 ou posterior** e inclui o texto GPLv3 em `LICENSE.txt`. As seções 4 e 5 permitem redistribuir código e modificações mantendo avisos, licença, identificação das alterações e data. Não foi encontrada nesses documentos uma proibição geral de publicar um conjunto independente de patches de MH Rise.

Este repositório preserva a licença e os avisos nos patches, identifica mudanças realizadas em 14–17/10/2026 e atribui a origem do emulador. A GPL não transfere ao mantenedor deste registro a propriedade do Eden nem concede aprovação dos desenvolvedores para o fix.

## Distribuição de APKs

A seção 6 da GPL trata da distribuição de código objeto. É necessário cumprir uma das formas previstas de disponibilizar o **Corresponding Source**, incluindo o código necessário e os scripts de build/instalação aplicáveis, com as dependências que não se enquadrem nas exceções da licença.

A release experimental disponibiliza o APK junto de pacotes da árvore modificada do Eden, fontes/dependências nativas e fontes/POMs Maven, scripts, avisos e checksums. Consulte [RELEASE.md](RELEASE.md). O commit base e o patch completo da release identificam o código correspondente; as bibliotecas pré-compiladas têm fontes e scripts dos respectivos fornecedores incluídos. A oferta de fonte não aponta apenas para o master atual nem apenas para os dois patches isolados.

Referências: [GPLv3](https://www.gnu.org/licenses/gpl-3.0.html), [README do Eden](https://git.eden-emu.dev/eden-emu/eden/src/branch/master/README.md), [CONTRIBUTING](https://git.eden-emu.dev/eden-emu/eden/src/branch/master/CONTRIBUTING.md).

## Regras de contribuição e uso de IA

As cópias de `UPSTREAM-AI-POLICY.md` e `UPSTREAM-CONTRIBUTING.md` registram as regras lidas. Contribuições ao Eden exigem declaração de IA, revisão/testes/responsabilidade humana e não aceitam mensagens de commit/PR integralmente geradas por IA. A política também restringe contribuições inteiramente geradas por agentes sem compreensão humana.

Esta publicação é um registro independente solicitado pelo jogador, com uso substancial de Codex declarado. Não é uma submissão upstream nem uma declaração de cumprimento da revisão humana exigida para aceitação pelo Eden. Testes manuais pelo jogador não equivalem a revisão humana integral do código.

O `AGENTS.md` upstream instrui agentes a não enviar pushes/PRs em nome do usuário. A publicação independente foi solicitada expressamente pelo usuário nesta sessão; não foi iniciada autonomamente nem enviada ao repositório oficial. A instrução explícita do usuário sobre a publicação prevalece sobre essa instrução local de fluxo de trabalho. Não atribuímos ao Eden autorização específica deste envio nem sugerimos que a licença elimine suas regras de contribuição.

## Procedimento para contribuir ao projeto oficial

O documento upstream descreve contribuições por Forgejo, mirrors e patches por e-mail em formato `git format-patch`. Uma contribuição futura precisa ser revisada e apresentada por uma pessoa, com explicação técnica, testes e declaração de IA, conforme a política em vigor naquele momento. Nenhum PR, comentário, issue ou e-mail ao projeto oficial foi enviado como parte desta publicação.

## Conteúdo excluído

Não foram incluídos jogos, keys de console, firmware, saves, tokens, chaves particulares de assinatura, configurações pessoais completas, endereços ADB, identificadores particulares do aparelho, dumps de shaders do jogo ou perfis brutos. A release inclui o APK e as fontes descritas acima; o histórico público resume as evidências sem expor dados particulares.
