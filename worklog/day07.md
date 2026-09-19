# Day 7 — Automation Prototype and Finalization

## Work Done

- Finalized `segments.jsonl` for Dataset B with 250 segmented work units and process labels.
- Finalized the main automation candidate: payroll-item note entry.
- Built a small Playwright prototype that locates the `#pi-note` field and fills the note automatically.
- Tested the prototype successfully with a sample payroll note.
- The actual internal payroll application was not available locally, so I used a local reproduction of the observed field for the prototype.

## What I Tried, What Failed, and What I Learned

I first tried connecting the prototype directly to the observed local payroll URL, but the application was not running and the connection was refused.

Instead of assuming the production system was available, I reproduced the observed DOM field locally and verified that the automation logic works.

The main learning was to keep the prototype narrow and validate the core automation step rather than spending time building a larger system without access to the real application.

## Final Decision

I limited the automation scope to payroll note entry. Record selection, note review, exception handling and final submission remain manual.

This keeps the prototype feasible while demonstrating the repetitive step identified from the logs.