# [Project Name] — Project Specification

> **Version:** 1.0
> **Created:** YYYY-MM-DD
> **Last Updated:** YYYY-MM-DD
> **Status:** 🟡 In Planning
>
> **Tip:** Use `AGENT_MD/spec_init.md` to generate this file from a brain dump rather than filling it in manually.
>
> Living document — the AI agent updates **Codebase Inventory**, **Decision Log**, and **Current Focus**
> at the end of every working session. Do not edit those sections manually.

---

## Current Focus
<!-- The agent updates this at the start of each session. -->
<!-- Humans: glance here to see what is actively being worked on. -->

- Nothing started yet — spec v1.0 just created.

---

## ⚠️ Critical Pre-Work (Do Before Any Feature Work)

<!-- List any blocking tasks: security issues, credential rotation, dependency updates. -->
<!-- Delete this section once all items are complete. -->

- [ ] _Example: rotate exposed API keys and remove from git history_
- [ ] _Example: update critical dependencies with known CVEs_

---

## Project Overview

<!-- One or two paragraphs describing what the project does and why it exists. -->

_[Describe your project here.]_

### Problem Statement

<!-- What pain does this solve and for whom? One focused paragraph. -->

_[Describe the problem this project solves.]_

### Target Users

<!-- Who uses this? What are their goals? What do they need most? -->

_[Describe your users and their needs.]_

### Current Operational Reality (as of YYYY-MM-DD)

<!-- What actually works today? What is deployed? What is in progress? -->
<!-- If this is a greenfield project, say so. -->

_[Describe the current state — what's working, what's deployed, what's in progress.]_

---

## Success Criteria (v1.0)

<!-- How do we know v1.0 is done? Make each criterion testable — pass/fail. -->

- [ ] _[Criterion 1 — specific and verifiable]_
- [ ] _[Criterion 2]_
- [ ] _[Criterion 3]_

---

## Constraints & Non-Negotiables

<!-- Anything the team cannot change: budget, compliance, deadlines, team size. -->

- **Team:** _[e.g., 2 developers, part-time]_
- **Timeline:** _[e.g., MVP in 8 weeks]_
- **Budget:** _[e.g., infrastructure must stay under $50/month]_
- **Compliance:** _[e.g., GDPR, SOC2, none]_
- **Non-negotiables:** _[e.g., must work offline, must support mobile browsers]_

---

## Tech Stack

### Current (what exists today)

| Layer | Technology | Notes |
|---|---|---|
| Language | _e.g., Python 3.12_ | |
| Framework | _e.g., FastAPI_ | |
| Database | _e.g., PostgreSQL 16_ | |
| Cache | _e.g., Redis 7_ | |
| Auth | _e.g., JWT (python-jose)_ | |
| Frontend | _e.g., HTMX + Jinja2_ | |
| Testing | _e.g., pytest, pytest-asyncio_ | |
| Containerisation | _e.g., Docker, Docker Compose_ | |
| CI/CD | _e.g., GitHub Actions_ | |

### Target (what we are building toward)

| Layer | Technology | Notes |
|---|---|---|
| _..._ | _..._ | _..._ |

---

## Architectural Principles

<!-- These are the rules the AI agent follows when making technical decisions. -->
<!-- Add, remove, or modify to match your project's philosophy. -->

- **API-first**: every capability exposed as a versioned REST endpoint
- **Async throughout**: no blocking I/O in request handlers
- **DB-primary**: the database is the authoritative data store; filesystem for artefacts only
- **TDD**: write tests before implementation; aim for >80% coverage on core logic
- _[Add your own principles here]_

---

## Codebase Inventory

<!-- The agent updates this table when files are created, moved, or deleted. -->
<!-- Do not edit manually — let the agent maintain it. -->

| File | Role | Status | Last Updated |
|---|---|---|---|
| `AGENT_MD/spec.md` | Living project specification | ✅ Active | YYYY-MM-DD |
| `AGENT_MD/plan/rules.md` | AI agent authoring conventions | ✅ Active | YYYY-MM-DD |
| _`src/main.py`_ | _Entrypoint_ | _✅ Active_ | _—_ |

---

## Feature Index

<!-- Status: [ ] Not started | 🔄 In progress | ✅ Complete | ⏸ Blocked -->
<!-- Agent updates Status column as work progresses. -->

| # | Feature | Status | Priority | Notes |
|---|---|---|---|---|
| 0 | Pre-Work: Security + Stability | [ ] | P0 | _Credentials, dependency audit, repo setup_ |
| 1 | _Feature name_ | [ ] | P0 | _Brief notes_ |
| 2 | _Feature name_ | [ ] | P1 | _Brief notes_ |
| _..._ | | | | |

---

## Known Issues & Technical Debt

<!-- Agent appends issues discovered during implementation. Humans can add items too. -->

- _Example: API rate limiting not implemented — risk of abuse at scale_
- _Example: Test suite has 3 flaky tests related to timing_

---

## Known Unknowns

<!-- Deliberately undecided. Revisit as the project matures. -->

- _[Something uncertain — e.g., "Final choice of auth provider not made"]_

---

## Decision Log

<!-- The agent appends one row here at the end of every session. -->
<!-- Do not edit manually — let the agent maintain it. -->

| Date | Decision | Rationale | Alternatives Considered |
|---|---|---|---|
| YYYY-MM-DD | Created v1.0 spec.md | Project initialisation | n/a |

---

---

# FEATURE 0 — Pre-Work: [Security / Stability / Setup]

## Goal

_[Describe the prerequisites and their importance — what must be true before feature work begins.]_

## Tasks

- [ ] Initialise git repository and set up `.gitignore`
- [ ] Set up environment variable management (`.env` + `.env.example`)
- [ ] _Other task_

## Verification

_[How to confirm pre-work is complete — e.g., "`git log --all -p | grep SECRET` returns nothing".]_

---

# FEATURE 1 — [Feature Name]

## Goal

_[What this feature achieves and why it matters.]_

## Existing Code to Reference

<!-- Agent: load these files into context at the start of the session for this feature. -->

- `src/relevant_file.py`

## Tasks

- [ ] _Task 1_
- [ ] _Task 2_

## Acceptance Criteria

- [ ] _[How to verify this feature works end-to-end]_
- [ ] _[Edge cases covered]_
