# Day 6 — Dataset B Analysis

## Goal
Apply the Dataset A segmentation approach to Dataset B and identify repetitive tasks suitable for automation.

## Results
- 15 sessions
- 20,477 events
- 250 segmented work units
- 9,587 seconds total segmented time
- 38.35 seconds average duration
- Microsoft Edge: 13,300 events
- `browser_form_input`: 608 events, all using paste

Repeated note fields:
- Payroll (`pi-note`): 233
- Leave (`la-note`): 136
- Onboarding (`ob-note`): 89
- Social insurance (`si-note`): 82
- Resident tax (`rt-note`): 68

## What I Tried, What Failed, What I Learned
I first tried extracting application and browser information using simple field parsing. This failed because important information was stored inside nested JSON fields such as `context.active_app`.
After inspecting the raw event structure, I updated the parser to extract the nested fields correctly.
I then analyzed `browser_form_input` events and initially extracted the wrong browser field. Inspecting an actual event showed that the useful information was available inside the browser-tab and payload data.
This helped identify a clear pattern: all 608 form-input events used the `paste` method.

## Automation Choice
I chose **payroll-item note entry** because it had the highest repetition (233 events) and used the same field repeatedly. I limited the scope to note entry rather than the full workflow to avoid automating decisions that may require human judgment.

## Implementation
A DOM-based browser automation is preferred over mouse/keyboard automation because the dataset exposes stable page and field information. Full backend/API automation was not considered because no suitable API was available.

## Manual Work & Impact
Users would still select/verify the correct record, prepare or review the note, handle exceptions, and submit the final action. The expected impact is reducing repetitive data entry rather than fully automating the process.

## Risks
Field/page changes may break the automation, and incorrect record selection could cause wrong entries. Stable selectors, validation, confirmation steps, exception handling, and a manual fallback would reduce these risks.

## Final Result
Dataset B analysis identified repetitive browser-based note entry as the main automation opportunity, with payroll-item note entry selected as the initial prototype scope.