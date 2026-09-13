# Day 2 — Comparing Ground Truth with Raw Events

## Goal

To compare ground-truth process boundaries with raw desktop
events from one Dataset A session and identify possible signals
for process segmentation.

## Work completed

- Created an Excel-based analysis for one Dataset A session.
- Reviewed important process boundaries from `gt.jsonl`.
- Compared raw `events.jsonl` activity around multiple boundaries.
- Created a `Raw Event Analysis` sheet.
- Recorded application transitions, browser/window activity,
  clipboard actions, keyboard interactions, and timing gaps.

## Boundaries analyzed

- H → C at 12:21:41.332
- C → B at 12:22:25.681
- B → A at 12:23:22.089
- A → M at 12:23:46.001

## Initial observations

Application changes alone do not consistently correspond to
process boundaries.

Other potentially useful signals include:
- application/window transitions
- browser/window switching
- clipboard and paste activity
- changes in business-context text
- interaction bursts
- timing gaps

These are preliminary observations and have not yet been
converted into a final segmentation algorithm.

## What I learned

A raw event timeline contains many low-level events that cannot
be directly treated as process boundaries. Ground-truth boundaries
need to be compared with the surrounding raw activity to identify
reliable signals.

## Next step

Analyze more examples from Dataset A and determine which signals
are consistent enough to form an initial segmentation approach.