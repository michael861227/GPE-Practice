---
name: gpe-readme-record
description: Use when updating this project's README.md # Record table for GPE solution files, including adding solved problems, editing Review/Master/Recommand/Appearance values, fixing GitHub cpp links, or re-sorting the Record table.
---

# GPE README Record

## Overview

Maintain the `README.md` `# Record` table for this GPE practice repo. Preserve the table's symbols, centered Markdown alignment, GitHub links, default values, and sorting rules.

## Table Format

Use exactly these columns and centered alignment:

```markdown
| Problem | Recommand | Appearance | Review | Master |
|:---:|:---:|:---:|:---:|:---:|
```

Field rules:
- `Problem`: show only the problem title, not the problem id; link to the GitHub `.cpp` file on the current repo's `master` branch.
- `Recommand`: use `⭐️`, `⭐️⭐️`, or `⭐️⭐️⭐️`.
- `Appearance`: use keycap numbers such as `1️⃣`, `4️⃣`, `8️⃣`.
- `Review`: use keycap numbers such as `0️⃣`, `1️⃣`, `2️⃣`.
- `Master`: use `⭐️`, `⭐️⭐️`, or `⭐️⭐️⭐️`.

Keep the user's spelling `Recommand`.

## Adding A Problem

When adding a solved problem that is not already in the table:
1. Confirm the matching `.cpp` file exists in the repo.
2. Use the website/GPE Helper data for the display title, `rating` as `Recommand`, and `Appearance` when available.
3. If the user does not specify values, default to `Review` as `0️⃣` and `Master` as `⭐️`.
4. Use the same symbol style already present in the table.
5. Insert the row, then re-sort the whole table.

If a filename and website title differ only by singular/plural or spacing, prefer the website title for display text and the actual repo filename for the GitHub link.

## Sorting

Sort rows by:
1. `Recommand` star count, high to low.
2. `Appearance` number, high to low.
3. `Master` star count, high to low.

If all three sort keys match, preserve the existing relative order to avoid unnecessary churn.

## Verification

Before finishing:
- Read the rendered table section with `sed -n '13,45p' README.md` or an equivalent command.
- Confirm the alignment row is still `|:---:|:---:|:---:|:---:|:---:|`.
- Confirm new or changed links point to existing `.cpp` filenames.
- Confirm rows are sorted by `Recommand -> Appearance -> Master` with star counts descending and Appearance descending.

## Git Publish

After the README update verification passes:
1. Run `git status`.
2. Run `git add .` to stage the current working tree changes.
3. Run `git commit -m "Update README.md"`.
4. Run `git push`.

If any git command fails, stop and report the exact failure instead of trying alternate history, force push, reset, checkout, or stash commands. Ask the user before taking any recovery action.
