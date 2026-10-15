# Pixel Vault

A rogue intern locked Adobe's brand kit inside **Pixel Vault** and walked out.
You're the new intern. Your job: break back in, one mission at a time.

## Start the vault

Open a terminal and run:

```bash
make start
```

The first start takes a little longer, because the vault is being compiled.
When it's ready, the website opens in your browser.
If it doesn't, open the **Ports** tab and click the address next to port 8080.

To stop the vault, press `Ctrl+C` in the terminal.

## How it works

- There are **8 missions**. Do them in any order.
- Every mission hides a **flag** that looks like `adbe{password}`.
- When you find a flag, paste it into the mission and press **Submit flag**.
- Stuck? Every mission has one hint.

## Your first flag

To get familiar with the platform, here is your first flag. It's scrambled:

```
bnFvcntjdTBnMGZ1MGNfY2UwfQ==
```

## Useful commands

| Command | What it does |
| --- | --- |
| `make start` | Builds the vault, runs the tests, and opens the vault |
| `make test` | Runs the tests only |
| `make reset` | Forgets all progress and starts over |

## What's inside

| Folder | What lives there |
| --- | --- |
| `frontend/` | The website: HTML, CSS and JavaScript ([more](frontend/README.md)) |
| `backend/` | The vault's server, written in C++ ([more](backend/README.md)) |
| `Makefile` | The commands above |

Everything in this repository is fair game. Good luck, intern.
