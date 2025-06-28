# Trabalho-de-AEDS-Fundamentos

## Estrutura do projeto
projeto/
├── codigo/                    # Código-fonte em C (.c e .h)
│   ├── main.c              # Menu principal e fluxo do programa
│   ├── produto.c
│   ├── produto.h
│   ├── vendedor.c
│   ├── vendedor.h
│   ├── comprador.c
│   ├── comprador.h
│   ├── venda.c
│   ├── venda.h
│   ├── nota_fiscal.c
│   └── nota_fiscal.h
│
├── data/                   # Arquivos de dados do sistema
│   ├── produtos.txt
│   ├── vendedores.txt
│   ├── compradores.txt
│   ├── vendas.txt
│   └── notas_fiscais.txt
│
├── testes/                  # Testes unitários e arquivos de testes
│   ├── test_produto.c
│   ├── test_venda.c
│   ├── test_vendedor.c
│   ├── test_comprador.c
│   ├── test_nota_fiscal.c
│   ├── test_main.c
│   └── munit/              # Biblioteca µnit para testes
│       ├── munit.h
│       └── munit.c
│
├── documentação/                   # Documentação e relatórios
│
├── build/                  # Binários e arquivos objeto (não versionado)
│   ├── obj/                # Arquivos .o compilados
│   └── bin/                # Executáveis finais (ex: programa, testes)
│
├── Makefile                # Script de compilação
└── README.md               # Descrição geral do projeto

