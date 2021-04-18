# Extracao-Z

# Introdução

O problema apresentado foi o de construir um programa que controla vários robôs em um planeta ficcional, o mesmo coletaria recursos minerais e exterminaria aliens a medida que prosseguisse com sua missão. No final, retornaria a base de operações e exibiria os seus resultados.

Para lidar com essa problemática foi feito o Programa “Extração Z”, que é um software criado com base na linguagem C/C++ que realiza a leitura de um mapa e de comandos preestabelecidos e os executas de acordo com uma ordem de prioridade, em seguida ele imprimirá em um arquivo de saída os acontecimentos resultantes de tais comandos.

Para tal programa ser desenvolvido, foi necessário a separação de responsabilidades. O main teve a atribuição de ler os arquivos passados como parâmetro de entrada e criar objetos de alto nível de complexidade, já o código secundário faz a manipulação desses objetos complexos de acordo a necessidade imposta, buscando utilizar as estruturas de dados, sempre que possível, aprendidas até o momento na disciplina Estruturas de Dados.


# Implementação

O código atual está subdivido em quatro pastas:

• Bin: Contém os arquivos .txt que serão utilizados como entrada do programa e o executável.

• Include: Contém o cabeçalho do código com as classes implementadas.

• Obj: Contém todos arquivos objetos advindos do processo da compilação Makefile.

• Src: Contém as outras implementações utilizadas no código, além do arquivo “main.cpp”, sendo este o arquivo base do programa.

As configurações de hardware e software usados para o desenvolvimento do programa são os seguintes:

    • Sistema Operacional: Windows 10 Home Single Language 
    
    • Processador: Intel® Core™ i7-7700HQ CPU @ 2.80GHz 2.81GHz
    
    • Placa de Vídeo: NVIDIA GTX 1050ti 4GB VRAM
    
    • Memória: 16GB RAM DDR4
    
    • Memória física: SSD M.2 240GB Leituras: 1.500MB/s e Gravações: 800MB/s 
    
    • Linguagem: C/C++
    
    • Compilador: Visual Studio Code + MinGW
    

Para a implementação desse programa foram utilizados vários tipos de estruturas de dados e funções, elas estão contidas no arquivo “Robo.h”, o funcionamento delas será explicado abaixo
.
• Class ListaEncadeada: É uma das principais TADs utilizadas para a criação do programa, ela é responsável por pegar os comandos que estão no arquivo .txt é armazená-los para ter um controle maior. Dentro de seus métodos, temos a inserção e remoção de elementos em quaisquer posições dessa lista, além da obtenção do conteúdo e do tamanho da lista.

• Class Robo: É responsável por armazenar as variáveis de cada robô utilizado, que no caso são o seu id, posição no mapa, estado de ativação, estado de execução, quantidade de aliens mortos e recursos coletados. Os seus métodos são simples, e são divididos entre mudar o valor/estado de suas variáveis e obter seu valor/estado.

• Class VetorRobos: A classe mais simples do programa, ela é responsável somente pela criação de um array de robôs, para que o controle sobre cada indivíduo seja melhor.

• Class Mapa: É responsável por criar uma matriz que condiz com o conteúdo do “mapa.txt”. Seus métodos são utilizados para retornar o número de linhas e colunas do mapa, além de imprimir o conteúdo do mapa no começo e no final do programa (após todas as modificações).

• Void criar_listaC: Recebe como parâmetro o objeto lista previamente criada pela classe ListaEncadeada e o arquivo “comandos.txt”. A partir dos dois, é criado uma lista encadeada já com a ordem de prioridade pronta.

• Int criar_listaE: É responsável por subdividir a listaC em cada execução e retorna qual o id do robô que recebeu o comando de execução. Recebe como parâmetro a listaC, o objeto lista previamente criada pela classe ListaEncadeada e a posição na qual o comando executar se encontra.

• Robo **criar_robos: Responsável por colocar cada robô dentro do array de robôs.

• Void destruir_robos: É responsável por desalocar da memória cada robô que foi criado pela função criar_robos.

• Void inicar: É a principal função do programa. Recebe como parâmetros os objetos ListaC e ListaE, o array de robôs, o mapa criado e o arquivo vazio de saída. Dentro dela será chamada a criação da ListaE, além de fazer a verificação dos elementos dentro da ListaE e a partir disso as ordens são executadas imediatamente. Com a execução dessas ordens, é definido o id do robô e as suas posições. As suas saídas são armazenadas dentro de uma lista de saída individual de cada Robô, tais listas de saídas só serão impressas caso seja solicitado um comando de relatório. Por fim, ela também é responsável por chamar o método de impressão do conteúdo do mapa e por em cada loop limpar uma porção da ListaC e da ListaE.

• Void printRelatório: É responsável por imprimir o relatório final de cada robô utilizado dentro do programa. Recebe como parâmetro o arquivo de saída, o id do robô que foi solicitado a impressão de relatório e o array de robôs.


# Instruções de compilação e execução

OBS1: As instruções dadas a seguir são para compilar o programa no sistema operacional Windows 10.

OBS2: No meu programa em específico, para manter uma organização e controle maior, preferi imprimir a saída dentro de um arquivo .txt que etá contido na pasta “bin”, ao invés de no terminal.

Para a execução do processo de compilação é necessário que navegue para a pasta em que o projeto está localizado. Primeiramente, caso seja feita alguma modificação dos arquivos .cpp ou .h é necessário refazer o Makefile do projeto, para isso é só executar no terminal o comando “make”. 

O executável do programa já estará pronto dentro da pasta “bin”, então para utilizá-lo é necessário saber o diretório do arquivo, após obtido um endereço que se parece com <C:\Users\Desktop\tp1\bin> copie toda a parte depois de “Users”, chame o seu prompt de comando, digite “cd” e em seguida cole o endereço copiado, por último é só digitar “run.out” que o programa rodará.
