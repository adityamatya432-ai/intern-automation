# Day 3 — Initial Segmentation Baseline

## Goal

Build an initial rule-based approach for detecting possible process
boundaries from raw desktop events.

## Work completed

- Implemented the first C++ log analysis program.
- Read and processed `events.jsonl`.
- Counted event types and analyzed timing gaps.
- Detected application changes and window/context changes.
- Combined these signals to create boundary candidates.
- Compared the candidates with known Dataset A ground-truth boundaries.

## Experiments

The first rule used multiple signals and produced too many candidate
boundaries.

A stricter rule requiring a time gap together with an application or
window change produced fewer candidates, but missed several true
boundaries.

## What I learned

No single signal is sufficient for reliable segmentation.
Process boundaries are often represented by a combination of
contextual and temporal changes.

## Current status

A working baseline for extracting segmentation signals has been
implemented. The boundary rule still needs validation and refinement.

## Next step

Improve the boundary detection rule on Dataset A and generate
preliminary process segments before applying the approach to Dataset B.