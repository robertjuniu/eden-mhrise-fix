# Save de MH Rise: Steam → Switch/Eden

Ferramenta externa recomendada para esse fluxo: [hashcade/mhrise-save-converter](https://github.com/hashcade/mhrise-save-converter), a versão derivada/fork indicada pelo jogador. O app gráfico se chama `mhrise-save-converter-gui`.

## Créditos

- **hashcade:** manutenção da versão derivada indicada acima.
- **Jing Haihan / jinghaihan:** autor original do [MHRise Save Converter](https://github.com/jinghaihan/mhrise-save-converter), conforme créditos e copyright preservados no README/LICENSE da versão hashcade. Licença **MIT**, copyright 2026 Jing Haihan.
- **kvasszn/ree-save-editor:** [pesquisa do formato dos saves](https://github.com/kvasszn/ree-save-editor), creditada pelo conversor.

O conversor não foi criado pelo mantenedor deste fix do Eden. Não há código ou binário do conversor incorporado ao APK/repositório; os links reconhecem o trabalho de seus autores. A licença MIT do conversor não muda a licença GPL do Eden.

O GitHub atualmente não marca a versão hashcade com a relação técnica `fork=true`; a descrição como versão derivada/fork segue o relato do jogador e os créditos de origem preservados no próprio repositório. Não se atribui a hashcade a autoria original do conversor.

## Resultado do teste do jogador

Em 17/10/2026, o jogador confirmou que **Steam → Switch funcionou após remover os slots 2 e 3 da cópia usada na conversão e manter apenas o personagem do slot 1**.

O chat anterior de suporte registrava erro em `data002Slot.bin` após processar parte dos arquivos. A orientação foi não usar uma saída parcial e repetir a conversão com uma cópia de origem contendo somente o slot desejado. A confirmação de sucesso foi fornecida posteriormente pelo jogador nesta investigação.

Esse resultado é um relato de caso. Não demonstra suporte universal a Steam → Switch, conversão correta de todos os campos, compatibilidade de todos os saves, nem necessidade de apagar outros slots para todos os usuários. O README do conversor ainda ressalvava que Steam → Switch e exclusão de slots precisavam de verificação em jogo.

## Como reproduzir com cuidado

1. Faça backup completo dos saves Steam e Switch/Eden. Trabalhe em **cópias**, preservando os originais. O conversor recomenda desativar temporariamente Steam Cloud durante os testes.
2. Use um save Switch/Eden existente como referência de destino (`Target save`), exigida pelo conversor para Steam → Switch. Ele é um template, não a pasta de saída.
3. Se ocorrer a mesma falha no slot 2 e você quiser apenas o personagem principal, prepare uma cópia que mantenha o slot 1: `data00-1.bin`, `data001Slot.bin` e arquivos do grupo `SS1_...`, quando existirem. Exclua da **cópia** os slots 2/3 correspondentes, como `data002Slot.bin`, `data003Slot.bin` e grupos `SS2_...`/`SS3_...`.
4. Não apague arquivos apenas por terem “2” ou “3” no nome: um arquivo `SS1_data002Slot.bin`, por exemplo, faz parte do grupo `SS1_...` citado no save de referência. Nomes de arquivos auxiliares não são uma regra suficiente para identificar o personagem.
5. No app, selecione a origem Steam, destino Switch, template de destino e uma pasta nova de saída; preencha seu próprio SteamID64 quando solicitado. Repita a conversão e confira que ela termina sem erro antes de importar o resultado no Eden.
6. Verifique o personagem e o progresso dentro do jogo, mantendo os backups. Não use uma saída gerada por uma conversão que parou com erro como se estivesse completa.

Consulte as instruções atuais do [fork](https://github.com/hashcade/mhrise-save-converter) e do [projeto original](https://github.com/jinghaihan/mhrise-save-converter). Links de download podem ser diferentes: o README consultado da versão hashcade apontava a seção de releases do autor original. Confira a origem do executável que baixar.

Nenhum save, SteamID ou arquivo particular do jogador é distribuído nesta documentação.
