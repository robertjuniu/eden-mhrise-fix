# Ferramentas auxiliares preservadas

`tools/frame_stats.py` lê a saída de `dumpsys SurfaceFlinger --latency` e analisa a segunda coluna (timestamps efetivos de apresentação), descartando zeros/sentinelas e ordenando timestamps únicos. Não controla o telefone e não mede diretamente tempo de GPU.

```sh
python tools/frame_stats.py frames.txt
python tools/frame_stats.py frames.txt --after 123456789
```

O resultado da amostra curta do lobby está em `lobby-frame-stats.json`. Os timestamps são monotônicos, não horários civis. A janela limitada de histórico não representa uma sessão longa.

`tests/pending_writes.cpp` é o teste sintético ARM64 do experimento PendingWrites, usando `common/range_sets.inc` da base Eden e seus includes Boost. Foi compilado pelo clang do NDK para `aarch64-linux-android28`, C++20, `-O1 -static-libstdc++`, com os diretórios de include do Eden e das bibliotecas Boost obtidas pelo CPM. O resultado no aparelho foi PASS para snapshot antigo, escritas pendentes novas, intervalos acumulados, snapshots sobrepostos, invalidação CPU e escrita disjunta. Não é um teste da correção IndexBound nem uma prova de que PendingWrites resolva MH Rise; o teste no jogo foi negativo.

Scripts locais de ADB continham caminhos/endereços particulares e não foram copiados. O mecanismo de A/B de FiveWordSync permanece documentado e visível no patch completo: com bits 32768+4096, o arquivo `config/mh-rise-sync-control.txt` controla 1/0; sem esses bits ele é inativo. Não é necessário para usar a referência validada.
