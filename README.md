# Hospital Management System 🏥

A C-based hospital management system for managing **patients**, **doctors**, and **appointments**. It uses **file I/O**, **Binary Search Trees (BST)**, and **queues** to simulate real-world hospital processes like appointment booking, priority management, and patient data storage.

---

## Features ✨
- **Patient Management**: Add, search, delete, and list patient records.
- **Doctor Management**: Add, delete, and list available doctors.
- **Appointment Scheduling**:
  - Uses **BST** for time-based sorting
  - Uses **Queue** for first-come-first-served order
- **Data Persistence**: All data is saved to `.txt` files (`/data` folder).
- **Modular Code**: Organized using `.h` and `.c` files for each module.

---

## How to Run 🚀

### Prerequisites
- **GCC** (Linux/Mac) or **MinGW** (Windows)
- Optional: **VS Code** or any C IDE

### Installation
1. Clone this repository:
   ```bash
   git clone https://github.com/yourusername/Management_Hospitality.git
   cd Management_Hospitality
   ```

2. Compile the program (manually or using a `Makefile` if added):
   ```bash
   gcc main.c patient.c doctor.c appointment.c utils.c -o hospital_system.exe
   ```

### Usage
```bash
./hospital_system.exe  # On Windows
./hospital_system      # On Linux/Mac
```

---

## Code Structure 📂

```bash
.
├── appointment.c       # Appointment logic (BST + Queue)
├── appointment.h
├── doctor.c            # Doctor management (vector)
├── doctor.h
├── patient.c           # Linked List for patient records
├── patient.h
├── utils.c             # File I/O and ID generator
├── utils.h
├── main.c              # Entry point for program logic
├── hospital_system.exe # Compiled output
├── run.exe             # Optional run binary
│
├── /data               # Text-based database
│   ├── appointments.txt
│   ├── doctors.txt
│   └── patients.txt
│
├── /.vscode            # VS Code project configs (safe to ignore in Git)
│   ├── settings.json
│   └── tasks.json
```

---

## Key Algorithms ⚙️
- **Binary Search Tree (BST)**:  
  Efficient appointment sorting and retrieval based on time  
  ⏱ Time Complexity: O(log n) insertion/search (average case)

- **Queue**:  
  Manages appointments in booking order (FIFO)

- **Linked List + Hashing**:  
  Stores patient data efficiently in memory

- **File I/O**:  
  Saves all information persistently in `.txt` files with plain text formatting

---

## Team 👥
- **Nguyen Huy Long**
- **Dinh Nguyen Phuong**

---

## License 📜
This project is licensed under the **MIT License** – see the [LICENSE](https://opensource.org/licenses/MIT) for details.
