# UBoard
Universal Board Game interface - create your own games - AI powered 


Utilisation de git en ligne de commande

1) initialiser git

mkdir basedir

cd basedir

git init

2) créer une copie locale (clone)

git clone https://github.com/Migou/UBoard.git

3) travailler en local

cd UBoard

#fichier existant

echo "bonjour" >> README.md

git commit

git push # envoie les modifs au serveur

#nouveau fichier

  mkdir src

  git add src

  echo '#include <stdio.h>\n printf("hello world")' >> src/test.cpp

  git add test.cpp

  git commit

  git push
