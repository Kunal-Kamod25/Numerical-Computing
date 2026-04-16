# [Project Name] — Current State Report

**Date:** YYYY-MM-DD
**Prepared for:** _[audience — e.g., project re-onboarding, sprint planning, AI agent context]_
**Scope:** _[what was audited — e.g., full source scan of `src/`, `web/`, config, tests]_

---

<!-- 
  HOW TO USE THIS FILE:
  
  This is a LIVING DOCUMENT. Update it after every major phase of work.
  New updates go at the TOP (reverse chronological), below this comment block.
  
  Format each update as:
  
  ## Update — YYYY-MM-DD [Phase/Plan Name]
  - Bullet summary of what changed
  - Test results: X passed, Y failed
  - Key files created/modified
  
  The numbered sections below (1–6) represent the BASELINE audit.
  Update them periodically to stay current.
-->

---

## 1. Executive summary

<!-- One paragraph: overall health of the codebase. Is it deployable? What's the biggest risk? -->

_[Describe the current state of the project — what works, what's broken, what's risky.]_

---

## 2. Source code inventory

<!-- List all significant files/modules with LOC and role. -->
<!-- Tip: run `find src/ -name '*.py' | xargs wc -l | sort -rn` to get LOC counts. -->

### Core files by size

| File | LOC | Role |
|---|---:|---|
| _`src/main.py`_ | _—_ | _Entrypoint_ |
| _`src/config.py`_ | _—_ | _Configuration_ |

### Web / API layer

| Component | Count | Key files |
|---|---:|---|
| Services | _—_ | _..._ |
| Routers | _—_ | _..._ |
| Tests | _—_ | _..._ |

---

## 3. Configuration audit

<!-- List actual config values, defaults, and any dangerous settings. -->

| Setting | Default | Source | Notes |
|---|---|---|---|
| _`DATABASE_URL`_ | _`sqlite:///local.db`_ | _env var_ | _..._ |

---

## 4. Test suite status

<!-- Run tests and record results. -->

| Suite | Passed | Failed | Skipped | Notes |
|---|---:|---:|---:|---|
| _Unit tests_ | _—_ | _—_ | _—_ | _..._ |
| _Integration_ | _—_ | _—_ | _—_ | _..._ |

---

## 5. Infrastructure & deployment

<!-- Docker images, CI pipelines, deployment targets. -->

| Component | Status | Notes |
|---|---|---|
| _Docker Compose_ | _..._ | _..._ |
| _CI pipeline_ | _..._ | _..._ |
| _Production deploy_ | _..._ | _..._ |

---

## 6. Known issues & technical debt

<!-- Bullet list of known problems. Reference plan numbers if fixes are planned. -->

- _Example: No rate limiting on public API endpoints (see PLAN-003)_
- _Example: Legacy module `old_handler.py` duplicates logic from `handler.py`_
