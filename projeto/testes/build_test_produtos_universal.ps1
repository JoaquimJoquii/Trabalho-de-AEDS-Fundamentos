# Compilação universal para rodar de qualquer pasta

$scriptPath = Split-Path -Parent $MyInvocation.MyCommand.Definition
cd $scriptPath

gcc ../codigo/produtos.c test_produtos.c munit/munit.c -I../codigo -Imunit -o test_produtos.exe

Write-Host "Compilação finalizada. Para rodar os testes, execute:"
Write-Host ".\test_produtos.exe"
