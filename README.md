# poekiller

## Setup (Windows, MSYS2 UCRT64)

Pré-requisito: [MSYS2](https://www.msys2.org/) instalado, rodando no terminal **UCRT64**.

### 1. Clonar

```powershell
git clone https://github.com/Vini-boat/poekiller.git
cd poekiller
```

### 2. raylib

```bash
pacman -S mingw-w64-ucrt-x86_64-raylib
```

### 3. clang-tidy

```bash
pacman -S mingw-w64-ucrt-x86_64-clang-tools-extra
```

(esse pacote traz o `clang-tidy`; o `build.ps1` já chama ele apontando pro toolchain do ucrt64)

### 4. Tracy

O código-fonte do Tracy já vem vendorizado em `third_party/public` — versão **0.13.1** (confira `third_party/public/common/TracyVersion.hpp` se quiser validar depois de um update).

Precisa baixar, da **mesma versão** (v0.13.1), o profiler compilado (o app que abre a UI e recebe a captura):

1. Vá em https://github.com/wolfpld/tracy/releases/tag/v0.13.1
2. Baixe o asset do Windows (o `.zip` com o `tracy-profiler.exe` / `Tracy.exe`)
3. Extraia em algum lugar fixo (ex: `C:\tools\tracy-0.13.1\`) e roda o executável quando for profilar

⚠️ Importante: sempre usar o profiler da **mesma versão** do código vendorizado, senão o protocolo não bate.

Se precisar recompilar o `TracyClient.o` (ex: trocou algo no third_party):

```bash
g++ -c third_party/public/TracyClient.cpp -DTRACY_ENABLE -O3 -Ithird_party/public -o out/TracyClient.o
```

### 5. Build

```powershell
.\build.ps1
```

Isso compila o `.exe` em `out\main.exe` e já roda o `clang-tidy` em seguida.
