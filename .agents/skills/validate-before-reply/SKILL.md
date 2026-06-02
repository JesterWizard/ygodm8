---
name: validate-before-reply
description: "Use when making code edits in this repo. Run `make test` (or `make test-host` for tools-only changes) before replying, and report failures instead of assuming the edit is safe."
---

# Validate Before Reply

## Use This Skill When

- You are editing code in this repo.
- You are about to finish and respond to the user.

## Rule

- The last step before replying must be **`make test`** when the change touches ROM code, hooks, RAM map, or custom gameplay.
- For **tools/manifest/tests-only** edits, **`make test-host`** is enough.
- If validation fails, report the failure clearly and do not claim the build passed.
- Do not skip validation because the change seems small.

## Workflow

1. Finish the code edit.
2. Run `make test` or `make test-host` (see rule above).
3. If validation passes, reply with the result.
4. If validation fails, fix the failure.
5. After intentional generator golden changes, run `make update-goldens` and commit `tests/goldens/`.

## Related Docs

- [documentation/tdd-framework.md](../../documentation/tdd-framework.md)
