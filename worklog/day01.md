# Day 1 — Understanding the Dataset

## Goal

Understand the structure of the operation logs and how business processes
are represented in Dataset A.

## What I learned

- `gt.jsonl` contains ground-truth information about processes and tasks.
- `events.jsonl` contains low-level computer activity.
- `run_id` identifies one complete recording/session.
- A single session can contain multiple different business processes.
- Different processes can be interleaved within the same session.
- The same process can appear multiple times in a session.
- Chunk boundaries are time-based and do not necessarily represent process boundaries.
- Noise or unrelated activity can also occur in the recording.

## Initial Dataset A observations

I inspected the beginning of one Dataset A recording.

The recording is associated with operator from the Human Resources
department and machine NB-M1-05.

The first business process observed was process H:
Bank Account Reconciliation.

At 12:21:12 UTC, process H started for case BR-175009-001.
Immediately afterward, a task for this case started with the action
"approve" for  (Chiba Bank).

## Initial understanding

The ground truth gives explicit information about process and task boundaries.
The main challenge will be to determine how similar boundaries can be
recovered from the raw `events.jsonl` data, where these labels are not directly
available.

## What I have not decided yet

I have not finalized the segmentation method yet. I first need to inspect
the corresponding raw events and identify useful signals such as application
changes, browser activity, keyboard/mouse activity, text and timing gaps.

## Next step

Inspect the corresponding `events.jsonl` events and compare them with the
ground-truth process timeline.