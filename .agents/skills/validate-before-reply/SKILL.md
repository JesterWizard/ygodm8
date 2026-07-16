---
name: validate-before-reply
description: "Use when making code edits in this repo. Always run `make` before replying, and report failures instead of assuming the edit is safe."
---

# Validate Before Reply

## Use This Skill When

- You are editing code in this repo.
- You are about to finish and respond to the user.

## Rule

Always run **`make`** (full ROM build). No shortcuts to narrower targets.

## Workflow

1. Finish the code edit.
2. Run `make`.
3. If validation passes, reply with the result.
4. If validation fails, fix the failure.
5. After intentional generator golden changes, run `make update-goldens` and commit `tests/goldens/`.

## Related Docs

- [documentation/tdd-framework.md](../../documentation/tdd-framework.md)
