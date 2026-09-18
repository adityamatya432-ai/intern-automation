
# Day 5 — Dataset A Segmentation Analysis

## Goal

Analyze event signals in Dataset A and identify a practical baseline for activity segmentation.

## Work completed

- Validated all 63 Dataset A sessions.
- Processed 162,768 events across the dataset.
- Compared ground-truth `process_switched_out` events with different event signals.
- Tested browser-context changes using tab ID, URL, and title.
- Tested `app_switch` payload changes using `new_app` and `previous_app`.
- Tested process/app changes with 2-second and 5-second time-gap filters.
- Observed that raw `app_switch` events are noisy and produce many false positives.
- Observed that adding a time-gap condition reduces candidate boundaries but also misses ground-truth boundaries.

## Results

| Rule | Candidates | GT matched | False positives |
|---|---:|---:|---:|
| Browser context | 914 | 78 | 836 |
| App/process change | 7209 | 1483 | 5726 |
| Strict process change | 5944 | 1462 | 4482 |
| Process change + 2 sec gap | 3877 | 1364 | 2513 |
| Process change + 5 sec gap | 1152 | 167 | 985 |

## Conclusion

The current event signals are noisy and no single tested rule provides a reliable final segmentation rule.

## Next step

Move to the next dataset/task and use the Dataset A analysis to guide further segmentation design.