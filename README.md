# Rede-de-sensores-ic do Alexandre 
[comment]: # (This actually is the most platform independent comment)
[comment]: # (https://stackoverflow.com/questions/4823468/comments-in-markdown)

[comment]: # (https://stackoverflow.com/questions/7653483/github-relative-link-in-markdown-file)
Uso github pages, como na configuração padrão ele abre este arquivo (README.md) então criei um link para os gráficos da rede de sensores.
   Simplesmente copiando os arquivos da aplicação web, os dados, gráficos, etc. são mostrados corretamente. A fonte de dados é o 
BD que Alexandre criou para o projeto. Quero usar os dados a partir de outra fonte.

Como a rede de sensores envia os dados para o firebase, então há algumas etapas de configuração do site que precisam ser feitas.
Uma delas é como configurar o firebase como fonte de dados para os gráficos. Como Alexandre usou snippets gerados pelo Firebase,
dá para reconstituir seus passos.

O main.js contém as chaves de configuração para acessar (o banco de dados) Firebase.
Os links que me ajudaram a entender o que foi feito são:
https://firebase.google.com/docs/web/setup#config-web-app
https://firebase.google.com/docs/projects/learn-more#config-files-objects
https://support.google.com/firebase/answer/7015592

Fazendo só o ajuste de main.js, a página aparece, mas os gráficos, números e tabela não. Lembrei agora que o dispositivo que estou usando tem MAC diferente dos que ele havia cadastrado. Isto pode ser um ponto - vou ajustar.

Ajustei o MAC em duas linhas do index.html, mas continua não mostrando...

Fiquei meio sem recursos. Acho improvável que seja conexão ou autenticação com canvas.js, ou algo com o bootstrap ou o popper (já que na conexão original funcionava).
Acho mais provável que não esteja vindo dado por algum motivo. Para checar isso quero ver alguns valores de variáveis. Vou incluir no html um <p /> para mostrar mensagens de depuração geradas dentro dos scripts.


## gráficos
veja os gráficos [aqui](web/index.html)
