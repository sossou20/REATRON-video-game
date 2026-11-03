# setup.sh — Environnement de dev en une commande

Script d'automatisation pour reconstruire mon environnement sur une **VM Debian vierge**.

## Ce que fait le script

- **Paquets** : `apt-get update` puis installation groupée (git, curl, wget, zsh, vim, tmux, htop, tree, jq, ripgrep, build-essential…)
- **Git** : `user.name`, `user.email`, éditeur par défaut, branche principale `main`, alias utiles
- **SSH** : génération d'une clé ed25519 si absente (affichée à la fin)
- **Shell** : Zsh + Oh My Zsh (thème `agnoster`, plugins autosuggestions / syntax-highlighting), défini comme shell par défaut
- **Dotfiles** : `.zshrc` et `.vimrc` déployés (depuis `./dotfiles/` s'il existe, sinon générés par le script)
- **Idempotent** : relançable sans erreur, rien n'est réinstallé, les fichiers existants différents sont sauvegardés en `.bak.<date>`

## Utilisation

```bash
git clone <url-du-depot> && cd <depot>
chmod +x setup.sh
sudo ./setup.sh
```

Personnalisation (optionnel) :

```bash
sudo GIT_NAME="Prenom Nom" GIT_EMAIL="moi@exemple.fr" ./setup.sh
```

## Notes

- Testé sur Debian vierge (EtnaCloud).
- Les erreurs réseau sont gérées avec des tentatives automatiques.
- Après exécution : `exec zsh` ou rouvrir le terminal.
