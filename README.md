
## Election Result Processing System
## Features

- **Secure Admin Panel** : Password-protected access using masked input (macOS/Linux compatible).
- **Voter Authentication** : Prevents double-voting using a unique ID verification system.
- **Data Persistence** : Saves and loads candidates and voter history using binary files.
- **XOR Encryption** : Obfuscates candidate data on the disk to prevent manual tampering.
- **Visual Dashboard** : Real-time results with ASCII-based progress bars and leaderboard tracking.
- **Audit Logging** : Maintains a transparent record of all Voter IDs that participated.

---

## 📂 Project Structure

| File | Description |
| :--- | :--- |
| `main.c` | Entry point; handles the primary menu and buffer management. |
| `admin.c` | Logic for adding candidates and viewing audit logs. |
| `auth.c` | POSIX-compliant password masking and authentication. |
| `election.c` | Core voting booth logic and eligibility checks. |
| `file_io.c` | Handles binary file I/O, memory allocation, and XOR encryption. |
| `ui.c` | Renders the visual dashboard and ASCII bar charts. |
| `models.h` | Global structures and constant definitions. |

---

## 🛠️ Installation & Setup

### Prerequisites
- **GCC Compiler**: Ensure you have `gcc` installed. (On Mac, run `xcode-select --install`).
- **Terminal**: Use a Unix-based terminal (macOS/Linux).

### Step 1: Clone and Prepare
Create the necessary data directory to avoid file I/O errors:
```bash
mkdir -p data
```

### Step 2: Compile
Compile all modules together using GCC:
```bash
gcc main.c auth.c file_io.c ui.c election.c admin.c -o election_system
```

### Step 3: Run
```bash
./election_system
```

---

## 🔐 Security Details

- **Admin Password**: The default password is `admin2026`.
- **Encryption**: The system uses a symmetric XOR cipher with a static key to protect the `election_data.dat` file. 
- **Integrity**: Memory is automatically decrypted for the UI and re-encrypted before disk writes.

---

## 📈 Future Roadmap
- [ ] Implement a "Delete Candidate" feature.
- [ ] Add a "Reset Election" administrative command.
- [ ] Integrate a GUI version using the GTK or Qt framework.

---
