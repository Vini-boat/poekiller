# compiler
$compiler = "g++"
$outputExe = ".\out\main.exe"

$cppVersion = "-std=c++20"
$optLevel = "-O3"

$warnings = @(
    "-Wall"
    "-Wextra"
    "-Wpedantic"
    "-Wconversion"
    "-Wsign-conversion"
)

$defines = @(
    "-DTRACY_ENABLE"
)

$includePaths = @(
    ".\include"
    ".\third_party\tracy\public"
)

$cppFiles = Get-ChildItem .\src -Filter *.cpp -Recurse |
    Select-Object -ExpandProperty FullName

$srcFiles = @(
    $cppFiles
    # ".\third_party\tracy\public\TracyClient.cpp"
    ".\src\TracyClient.o"
)

# raylib
$raylibDeps = @(
    "-lraylib"
    "-lopengl32"
    "-lgdi32"
    "-lwinmm"
)

# build command

$includeArgs = $includePaths | ForEach-Object { "-I$_" }

$allArgs = @(
    $cppVersion
    $optLevel
    $warnings
    $defines
    "-o"
    $outputExe
    $srcFiles
    $includeArgs
    $raylibDeps
)

$cmd = "$compiler $($allArgs -join ' ')"

Write-Host $cmd
Invoke-Expression $cmd

# clang-tidy

$toolchain = "--gcc-toolchain=C:/msys64/ucrt64/ -target x86_64-w64-mingw32"

$tidyCmd = "clang-tidy .\src\*.cpp -- $cppVersion $toolchain"
Write-Host $tidyCmd
Invoke-Expression $tidyCmd