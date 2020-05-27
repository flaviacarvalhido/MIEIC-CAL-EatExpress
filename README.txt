Lista de depend�ncias:
    - API Graphviewer
    - Standard Library
    - Ficheiros DeliveriesPorto.txt, DeliveriesPorto2.txt, DeliveriesPorto3.txt, DeliveriesPorto4.txt, DeliveriesPorto5.txt, DeliveriesPorto6.txt, DeliveriesPorto7.txt,
    DeliveriesViseu.txt, DeliveriesViseu2.txt, DeliveriesViseu3.txt, DeliveriesViseu4.txt, DeliveriesViseu5.txt, DeliveriesViseu6.txt, DeliveriesViseu7.txt, Restaurants.txt, restaurantsViseu.txt,
    Deliverers.txt 
    - Ficheiros dos mapas disponibilizados

A compila��o do programa deve ser feita com um compilador standard. 
Para os nossos testes, corremos o programa no IDE CLion, tal como indicado nas aulas pr�ticas.

Caso esteja a dar problemas, no CLion, no separador "File", aceda a "New CMake Project from Sources", escolha a pasta
do projeto, depois "Import as a new CMake Project" e selecione todos os .cpp e .h. Caso a aplica��o Java n�o corra, adicione no CMakeLists a linha 'link_libraries(ws2_32 wsock32)' e fa�a reload.

Para ver o mapa de Viseu, tem que puxar o cursor para a esquerda.