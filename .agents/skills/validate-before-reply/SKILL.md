---
name: validate-before-reply
description: "Use when making code edits in this repo. Always run `make` as the final step before replying, and report build failures instead of assuming the edit is safe."
---

# Validate Before Reply

## Use This Skill When

- You are editing code in this repo.
- You are about to finish and respond to the user.

## Rule

- The last step before replying must be `make -j6`.
- If `make` fails, report the failure clearly and do not claim the build passed.
- Do not skip validation because the change seems small.

## Workflow

1. Finish the code edit.
2. Run `make`.
3. If the build passes, reply with the result.
4. If the build fails, fix the failure.
