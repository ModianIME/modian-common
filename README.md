# Scriptorium Felt

[![License](https://img.shields.io/badge/License-Apache_2.0-blue.svg)](https://opensource.org/licenses/Apache-2.0)

`scriptorium-felt` is the core infrastructure and protocol SDK for the [Scriptorium IME](https://github.com/ScriptoriumLab) (Input Method Editor) ecosystem. It is a set of pure, modern C++ and CMake-based foundational component libraries.

## Vision

When building a cross-platform, high-performance modern input method, we physically isolate the complex "business brain" (Inkstone) from the "system UI/hooks" (Brush). `scriptorium-felt` was born to enable these isolated components to collaborate seamlessly and with ultra-low latency.

Our ultimate goals are:
1. **Building a Cross-Boundary Consensus**: Providing a unified Inter-Process Communication (IPC) mechanism, protocol definitions, and logging infrastructure across the entire ecosystem.
2. **Frictionless Integration**: Serving as an SDK for the third-party developer ecosystem. In the future, developers can simply include this library to easily build customized plugins for Scriptorium.
3. **Zero-Intrusion Clean Architecture**: Strictly adhering to the Dependency Inversion Principle (DIP). Highly modularized to completely decouple core business logic from OS-specific APIs.

---

## Architecture

This repository strictly follows Clean Architecture principles and is divided into the following core layers (CMake targets):

* **Core (`scriptorium::felt::core::*`)**
  The pure domain layer. Contains zero-dependency pure virtual interfaces (e.g., `iasync_ipc_server`) and core data structures (Protocol Structs).
* **Service (`scriptorium::felt::service::*`)**
  The protocol processing layer. Responsible for converting between underlying data and core domain models (e.g., JSON serialization and deserialization).
* **Infra (`scriptorium::felt::infra::*`)**
  The infrastructure implementation layer. Embraces OS-specific APIs and heavy third-party libraries (e.g., Windows Named Pipe IPC implementations, Spdlog wrappers, and charset utilities).
* **Test Infra (`scriptorium::felt::test_infra::*`)**
  Provides unified mocks and testing scaffolds for the entire ecosystem.

---

## Getting Started

This library natively supports CMake's `FetchContent`, allowing for extremely smooth integration into your C++ projects.

*(Detailed API documentation and code examples will be added upon the official 1.0 release.)*

---

## License

Licensed under the **Apache License 2.0**.

See `LICENSE` for details.

---

*Copyright © 2026 ScriptoriumLab.*
