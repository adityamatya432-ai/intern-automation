# Day 2 — Comparing Ground Truth with Raw Events

## Goal

To compare ground-truth process boundaries with raw desktop events from one Dataset A session and identify useful signals for
process segmentation.

## Work completed

- Created an Excel-based analysis for one Dataset A session.
- Reviewed important process boundaries from `gt.jsonl`.
- Compared raw `events.jsonl` activity around selected boundaries.
- Created a `Raw Event Analysis` sheet.
- Observed application/window changes, browser activity,
  clipboard/paste, keyboard/mouse activity, business context,
  and timing gaps.

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

Reliable segmentation will likely require multiple signals instead of
a single event type.

## Segmentation direction

I will use multiple signals such as:

- application/window changes
- business-context changes
- interaction patterns
- timing gaps

The first implementation will be rule-based and will be validated against Dataset A ground truth.

## Next step

Build an initial rule-based segmentation baseline and validate it
against Dataset A ground truth.