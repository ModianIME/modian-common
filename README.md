# Scriptorium Felt

[![Scriptorium Felt CI](https://github.com/ScriptoriumLab/scriptorium-felt/actions/workflows/scriptorium-felt-ci.yml/badge.svg)](https://github.com/ScriptoriumLab/scriptorium-felt/actions/workflows/scriptorium-felt-ci.yml)

[![License](https://img.shields.io/badge/License-Apache_2.0-blue.svg)](https://opensource.org/licenses/Apache-2.0)

> Shared infrastructure, IPC, and protocol foundations for the Scriptorium input method framework.

**Scriptorium Felt** is the shared foundation layer of the [Scriptorium](https://github.com/ScriptoriumLab) input method ecosystem.

It provides reusable protocol definitions, IPC abstractions and implementations, logging infrastructure, common utilities, and testing support used across independently evolving Scriptorium components.

Felt exists to keep shared technical concerns explicit and reusable without coupling the input-method core, platform integrations, or presentation layer to each other's implementations.

---

## Role in Scriptorium

Scriptorium is designed as a multi-process input method architecture with clear ownership boundaries between platform integration, input-method logic, presentation, and shared infrastructure.

![Scriptorium Architecture](assets/Scriptorium%20Architecture%20V1.1.1.png)

Felt provides the common boundaries that allow these components to communicate and share infrastructure without sharing their internal implementation details.

In particular:

- **[Scriptorium Brush](https://github.com/ScriptoriumLab/scriptorium-brush)** integrates Scriptorium with Windows through the Text Services Framework (TSF).
- **[Scriptorium Inkstone](https://github.com/ScriptoriumLab/scriptorium-inkstone)** owns input-method state and core logic such as composition, segmentation, candidate generation, and dictionary access.
- **[Scriptorium Ink](https://github.com/ScriptoriumLab/scriptorium-ink)** renders candidate windows and other user-facing state without owning input-method business state.
- **Scriptorium Felt** provides shared protocols, infrastructure abstractions, and reusable technical foundations used across those boundaries.

Felt is deliberately not the input-method engine, platform adapter, or UI.

Its responsibility is to provide the common ground on which those components can evolve independently.

---

## What Felt Provides

Felt is organized around a small set of shared technical responsibilities.

### Protocol Definitions

Felt defines the common data structures and protocol models exchanged between Scriptorium processes.

These models provide an explicit contract between independently evolving components such as Brush, Inkstone, and Ink.

Examples include:

- input events
- composition commands
- candidate and render state
- user actions
- shared protocol-level data structures

Protocol ownership belongs here rather than being duplicated inside individual platform or application components.

### IPC

Felt provides abstractions for inter-process communication together with infrastructure implementations.

The goal is to allow application code to depend on stable interfaces rather than directly depending on operating-system IPC APIs.

Current infrastructure includes Windows Named Pipe based communication.

The IPC boundary is intentionally designed so that platform-specific transport choices remain replaceable implementation details.

### Logging and Common Infrastructure

Felt contains shared infrastructure that would otherwise be duplicated across Scriptorium processes, including:

- logging abstractions and implementations
- character and encoding utilities
- reusable infrastructure helpers
- shared low-level types and utilities

### Testing Infrastructure

Felt also provides shared testing support for the wider Scriptorium ecosystem.

This includes common mocks, test doubles, and infrastructure scaffolding that allow components to test against stable shared boundaries without depending on production implementations.

---

## Architecture

Felt separates stable abstractions from infrastructure details through explicit dependency boundaries.

```text
┌──────────────────────────────────────────────┐
│                 Application                  │
│          Brush / Inkstone / others           │
└──────────────────────┬───────────────────────┘
                       │
                       ▼
┌──────────────────────────────────────────────┐
│                    Core                      │
│ Interfaces · Protocol Models · Shared Types  │
└──────────────────────▲───────────────────────┘
                       │
              depends toward Core
                       │
┌──────────────────────┴───────────────────────┐
│                  Service                     │
│   Protocol Conversion · Serialization        │
└──────────────────────▲───────────────────────┘
                       │
┌──────────────────────┴───────────────────────┐
│                   Infra                      │
│ Named Pipes · Logging · Platform Utilities   │
└──────────────────────────────────────────────┘
```

The important constraint is the dependency direction:

> Stable abstractions should not depend on infrastructure details.

Operating-system APIs, serialization libraries, logging implementations, and other replaceable technologies remain outside the core abstractions.

### Core

The Core layer contains stable interfaces and shared data structures.

Examples include:

- IPC interfaces such as `iasync_ipc_server`
- protocol models
- shared domain-neutral types

The Core layer avoids dependencies on operating-system APIs and heavy infrastructure libraries.

### Service

The Service layer handles transformations between protocol representations and core models.

Examples include:

- JSON serialization and deserialization
- protocol conversion
- message encoding and decoding

This keeps representation-specific concerns outside the stable protocol abstractions.

### Infra

The Infra layer contains concrete technical implementations.

Examples include:

- Windows Named Pipe IPC
- logging implementations
- character encoding utilities
- operating-system specific infrastructure

Infrastructure is replaceable and depends inward on the abstractions it implements.

### Test Infra

The Test Infra layer provides reusable testing support across Scriptorium repositories.

It contains common mocks, test doubles, and fixtures for shared Felt interfaces and protocol boundaries.

---

## Design Principles

### Shared Boundaries, Not Shared Business Logic

Felt exists to share contracts and infrastructure, not input-method behavior.

Candidate generation, segmentation, composition state, dictionary lookup, and other input-method decisions belong to Inkstone.

Platform behavior belongs to the corresponding platform adapter.

Presentation behavior belongs to Ink.

This prevents Felt from gradually becoming a catch-all dependency containing unrelated business logic.

### Platform Independence Where It Matters

Felt does not attempt to make every implementation platform-independent.

Instead, it keeps **interfaces and shared contracts** independent from platform-specific implementations.

For example, Windows Named Pipes may be used today as an IPC transport, while application code depends on an abstraction that can support different implementations in the future.

### Explicit Dependency Direction

Infrastructure depends on abstractions rather than abstractions depending on infrastructure.

This keeps replaceable technical choices—such as IPC transports, serializers, and logging libraries—from leaking into higher-level components.

### Evolution Without Lock-In

Today's implementation choices should not unnecessarily constrain tomorrow's architecture.

Felt therefore prefers stable boundaries around replaceable technologies rather than exposing implementation details throughout the ecosystem.

---

## Using Felt

Scriptorium Felt is built with modern C++ and CMake and is designed to be consumed as a dependency by other Scriptorium repositories.

It supports CMake's `FetchContent` mechanism.

A typical integration looks like:

```cmake
include(FetchContent)

FetchContent_Declare(
    scriptorium_felt
    GIT_REPOSITORY https://github.com/ScriptoriumLab/scriptorium-felt.git
    GIT_TAG master
)

FetchContent_MakeAvailable(scriptorium_felt)
```

Consumers can then link against the Felt targets required by their component.

For example:

```cmake
target_link_libraries(
    my_target
    PRIVATE
        scriptorium::felt::core
)
```

Available targets depend on the required layer and infrastructure capabilities.

> For reproducible production builds, consumers should pin Felt to a specific release tag or commit rather than relying on `master`.

---

## Building

### Prerequisites

- CMake 3.25+
- a C++23-compatible compiler
- Ninja or another supported CMake generator

### Configure

```bash
cmake -B build -G Ninja
```

### Build

```bash
cmake --build build
```

### Run Tests

```bash
ctest --test-dir build --output-on-failure
```

---

## Project Status

Scriptorium Felt is under active development together with the wider Scriptorium architecture.

Its APIs and internal structure may continue to evolve while the cross-platform process boundaries and shared protocols are refined.

The long-term goal is to keep Felt small, stable, and focused on infrastructure and shared contracts rather than allowing it to become a general-purpose dependency for unrelated application logic.

---

## Why "Felt"?

The Scriptorium repositories use traditional writing tools as an architectural metaphor.

A writing felt sits beneath the paper and provides a stable surface for the act of writing.

Likewise, **Scriptorium Felt** provides the underlying technical foundation on which the rest of Scriptorium operates.

It is not the brush, ink, or inkstone itself—but it supports the system beneath them.

---

## License

Licensed under the **Apache License 2.0**.

See `LICENSE` for details.

---

*Copyright © 2026 ScriptoriumLab.*
