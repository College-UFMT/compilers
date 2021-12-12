# Trabalho 1 -Código refatorado com gramática ampliada
## Autor: Kaio Felipe Nink Cardoso
## Disciplina: Compiladores
## Professor: Ivairton

<p>
Neste trabalho, você deverá usar como referência os códigos de <a href="https://github.com/College-UFMT/compilers/tree/main/Examples">Exemplo número 4 e 5 </a>.
Você deve implementar uma nova versão para o sistema apresentado no Exemplo 5 (Refatoração do código, primeira versão com analisador léxico) de tal maneira que ele reconheça a mesma gramática implementada no Exemplo 4 (Análise sintática com TAS).
Saiba que o código/comando em Assembly para multiplicação é:
</p>
<code>
<strong>mult</strong> rax, rbx
</code>

#### Gramática:
<ul>
    <li>E->TE'</li>
    <li>E'->+TE' | E'-> -TE'| vazio</li>
    <li>T->FT'</li>
    <li>TR->*FT' | TR->/FT' | vazio</li>
    <li>F->(E)</li>
</ul>

#### Github: <a href="https://github.com/College-UFMT/compilers">kaio-nink/compilers</a>