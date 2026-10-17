# Reconstrução e origem dos patches

## Base exata

```sh
git clone --recursive https://git.eden-emu.dev/eden-emu/eden.git eden-mhrise-source
cd eden-mhrise-source
git checkout --detach 14da4482a4668928bad43bb67ef12f96b9c9d972
git submodule update --init --recursive
git apply --check /caminho/eden-mhrise-fix/patches/validated-mhrise-full.patch
git apply /caminho/eden-mhrise-fix/patches/validated-mhrise-full.patch
git diff --check
```

O comando usa o snapshot completo validado, inclusive experimentos desligados. Para reconstruir o estado posterior com AppletRing, use `current-experiments-full.patch` **no lugar** do patch validado, sobre uma cópia limpa da mesma base. Os patches isolados/arquivados não devem ser aplicados cumulativamente sem inspeção.

Consulte o [guia oficial de build](https://git.eden-emu.dev/eden-emu/eden/src/branch/master/docs/Build.md) e a documentação Android contida no commit base. A documentação atual do upstream pode mudar; prefira a versão daquele commit ao reproduzir esta investigação.

## Ferramentas usadas

- Windows, PowerShell, Java 21.0.12.
- Gradle wrapper 8.13, Android SDK 36.
- Android NDK 28.2.13676358 e CMake 3.31.6.
- Dependências/submódulos/CPM determinados pelo código base e pelos scripts upstream.

Exemplo PowerShell, na pasta `src/android` do clone modificado:

```powershell
$env:JAVA_HOME = 'C:\caminho\jdk-21'
$env:ANDROID_HOME = 'C:\caminho\Android\Sdk'
$env:ANDROID_SDK_ROOT = $env:ANDROID_HOME
$env:CMAKE_BUILD_PARALLEL_LEVEL = '4'
.\gradlew.bat :app:assembleMainlineRelWithDebInfo --console=plain --max-workers=4 '-Dorg.gradle.jvmargs=-Xmx4g -XX:MaxMetaspaceSize=1g -Dfile.encoding=UTF-8'
```

Saída esperada:

```text
src/android/app/build/outputs/apk/mainline/relWithDebInfo/app-mainline-relWithDebInfo.apk
```

Use o mecanismo de assinatura de desenvolvimento previsto no projeto; não publique chaves pessoais. Uma assinatura diferente pode impedir atualização por cima de outro APK. Não desinstale uma instalação com dados importantes sem backup.

O hash publicado identifica a build local testada, não uma promessa de reprodução binária bit a bit. Metadados de build, assinatura e ambiente podem alterar o SHA-256 de uma reconstrução equivalente.

## Configuração

No snapshot validado: `debug_knobs=16392` (sampler 8 + IndexBound 16384), GPU Low, DMA e fences no padrão, resolução 1×, modo portátil, caches preservados. Dumps e diagnósticos estão desligados. Configurações por jogo devem herdar esses valores ou configurar os mesmos explicitamente.

O arquivo `config/mhrise-reference.ini` é um fragmento de referência, não um perfil completo pronto para sobrescrever os dados do aplicativo. As opções podem mudar de seção ou significado em outras revisões. As flags reutilizadas nesta investigação não são compatíveis numericamente com todos os APKs históricos.

## Instalação

O APK experimental e as fontes correspondentes estão na [release](RELEASE.md). Use o patch `release-mhrise-full.patch` em vez do validado ao reconstruir a versão com nome visível Eden e correções ativas por padrão. Se extrair o pacote de fontes da release, ele já está modificado; não aplique o patch novamente. Use somente o conteúdo necessário que você possui legitimamente. Não fornecemos jogos, keys de console, firmware ou dumps do jogo.

Se for publicar um binário derivado, prepare antes uma distribuição do código-fonte correspondente completo e sua cadeia de dependências/build, preservando as licenças. Consulte `PUBLICATION.md`.
