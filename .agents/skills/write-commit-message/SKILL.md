---
name: write-commit-message
description: >-
  Summarize staged git changes into a concise bullet list and write it into
  .git/COMMIT_EDITMSG. Use when the user asks to write a commit message,
  draft a commit message, fill in the commit message, or summarize changes
  for a commit.
---

# Write Commit Message

Draft a commit message from staged changes and insert it into the open commit editor file. Do **not** run `git commit` unless the user explicitly asks to commit.

## Workflow

1. **Gather changes** — run in parallel:
   - `git diff --cached` (primary source; commit message describes staged work)
   - `git diff --cached --stat`
   - `git status`
   - Read `.git/COMMIT_EDITMSG` if it exists

2. **Summarize** — produce:
   - One subject line (≤72 chars): `[Category] - Short summary` matching recent repo style (e.g. `FEATURE - …`, `Debug - …`, `Fix - …`)
   - A blank line
   - 3–8 bullet points covering **what changed and why**, grouped by theme — not a raw file list

3. **Write the file** — edit `.git/COMMIT_EDITMSG`:
   - Replace any existing non-comment text at the top with the new subject + bullets
   - **Preserve every `#` comment line** Git added (branch info, staged file list, instructions) exactly as-is, in original order
   - Do not add `#` prefixes to the message body

4. **Reply briefly** — show the written message in chat; do not commit.

## Bullet guidelines

- Lead with user-visible or architectural impact, not filenames
- Merge related edits into one bullet (e.g. mixer asm + config + docs → one bullet)
- Use `-` list markers
- Skip noise: formatting-only churn, generated files unless they are the point of the change
- Past tense or imperative — match subject line tone

## Example output written to COMMIT_EDITMSG

```
FEATURE - Add voice asset pipeline hooks

- Wire HQ mixer voice slots through ram_map and ldscript
- Regenerate voice_assets_generated.s from updated manifest
- Document IWRAM budget impact in iwram-free-space.md
- Extend apply_lynjump.py to patch new mixer symbols

# Please enter the commit message for your changes. Lines starting
# with '#' will be ignored, and an empty message aborts the commit.
#
# ...
```

## Edge cases

- **Nothing staged**: say so; offer to stage files or use `git diff` for unstaged work — do not write an empty message
- **No COMMIT_EDITMSG**: write subject + bullets in chat only; tell user to open the commit editor or run `git commit` to create the file
- **Partial message already typed**: keep user wording that still applies; append or refine bullets below their subject if they wrote one
