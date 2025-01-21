# Code Système Reel to Reel

## Guide d'installation

### 1. Télécharger le répertoire Git

Vous pouvez télécharger le projet de deux manières :  
- **Via ZIP** : Téléchargez le fichier ZIP depuis GitHub et extrayez-le.  
- **Via Git** : Clonez le répertoire en utilisant la commande suivante :

    git clone https://github.com/LouisDebrulle/Reel_2_Reel

Ensuite, accédez au dossier cloné :

    cd Reel_2_Reel

---

### 2. Installer l'extension PlatformIO dans VS Code

- Ouvrez **VS Code**.  
- Accédez à l'onglet **Extensions** .  
- Recherchez **PlatformIO IDE** et installez-le.

---

### 3. Installer les bibliothèques Python requises

Assurez-vous d'avoir Python installé, puis exécutez la commande suivante pour installer les dépendances :

    pip install -r requirements.txt

---

### 4. Compiler et flasher le code sur le microcontrôleur

- Ouvrez le projet dans **VS Code**.  
- Dans l'onglet **PlatformIO**, cliquez sur "Build" pour compiler le code.  
- Ensuite, cliquez sur "Upload" pour flasher le microcontrôleur.

---

### 5. Exécuter le programme Python

Lancez le programme de visualisation avec la commande suivante :

    python output\visu_main.py

Cela permet d'afficher les données en temps réel.

---

