# Day 2 — Comparing Ground Truth with Raw Events

## Goal

Compare GT process boundaries  of a session with raw desktop events and identify useful signals for segmentation.

## Work completed

- Analyzed first session from  Dataset A  using `gt.jsonl`.
- Identified important process boundaries.
- Compared raw `events.jsonl` around selected boundaries.
- Created an Excel analysis with a `Raw Event Analysis` sheet.
- Observed app/window changes, browser activity, clipboard/paste,keyboard/mouse activity, business context, and timing gaps.

## Boundaries analyzed

- H → C
- C → B
- B → A
- A → M
- B suspended → H
- H → J

## Key observations

- Application switching alone is not enough.
- Browser/window and business-context changes can help.
- Clipboard and interaction patterns are useful supporting signals.
- Suspended/resumed processes make segmentation non-contiguous.

## What I learned

Reliable segmentation will likely require multiple signals instead of a single event type.

## Segmentation direction

I will use multiple signals such as:
- application/window changes
- business-context changes
- interaction patterns
- timing gaps

The first implementation will be rule-based and will be validated against Dataset A ground truth.

## Next step

Build an initial rule-based segmentation baseline and validate it against Dataset A ground truth.
