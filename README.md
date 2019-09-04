# Rede-de-sensores-ic do Alexandre 
[comment]: # (This actually is the most platform independent comment)
[comment]: # (https://stackoverflow.com/questions/4823468/comments-in-markdown)

[comment]: # (https://stackoverflow.com/questions/7653483/github-relative-link-in-markdown-file)
Uso github pages, como na configuração padrão ele abre este arquivo (README.md) então criei um link para os gráficos da rede de sensores.

Como a rede de sensores envia os dados para o firebase, então há algumas etapas de configuração do site que precisam ser feitas.
Uma delas é como configurar o firebase como fonte de dados para os gráficos. Como Alexandre usou snippets gerados pelo Firebase,
dá para reconstituir seus passos.

O main.js contém as chaves de configuração para acessar (o banco de dados) Firebase.
Os links que me ajudaram a entender o que foi feito são:
https://firebase.google.com/docs/web/setup#config-web-app
https://firebase.google.com/docs/projects/learn-more#config-files-objects
https://support.google.com/firebase/answer/7015592


## gráficos
veja os gráficos [aqui](web/index.html)
