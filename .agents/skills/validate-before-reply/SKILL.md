---
name: validate-before-reply
description: "Use when making code edits in this repo. Run the narrowest validation target that covers the change (`make test-cards`, `make test-cards-build`, `make test-host`, or `make test`) before replying, and report failures instead of assuming the edit is safe."
---

# Validate Before Reply

## Use This Skill When

- You are editing code in this repo.
- You are about to finish and respond to the user.

## Rule

Pick the **narrowest** target that still covers the edit:

| Change | Run |
|--------|-----|
| Custom card (manifest only) | `make test-cards` |
| Custom card + effect hooks and/or `configs/runtime.c` | `make test-cards-build` |
| Tools / manifest / tests only (no ROM) | `make test-host` |
| Events, LynJump, RAM map, or broad gameplay | `make test` |

- **`make test-cards`** — manifest, trunk, RAM card-growth; no events, no full ROM.
- **`make test-cards-build`** — `test-cards` + `make all` (proves hooks link).
- Do not default to **`make test`** for card-only work.
- If validation fails, report the failure clearly and do not claim the build passed.

## Workflow

1. Finish the code edit.
2. Run the target from the table above.
3. If validation passes, reply with the result.
4. If validation fails, fix the failure.
5. After intentional generator golden changes, run `make update-goldens` and commit `tests/goldens/`.

## Related Docs

- [documentation/tdd-framework.md](../../documentation/tdd-framework.md)
