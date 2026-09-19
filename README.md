# Operational Log Analysis & Automation Proposal

**Full Name:** Aditya Ambara Matya  
**University:** Indian Institute of Technology Goa (IIT Goa)  
**Department/Major:** Mathematics and Computing  
**Email:** aditya.ambara.24033@iitgoa.ac.in

## What this repository contains

- Step 1: Work segmentation
- Step 2: Dataset B analysis
- Step 3: Payroll note-entry prototype

## Project Flow

Raw Logs  
↓  
Work Segmentation  
↓  
Dataset B Analysis  
↓  
608 Form Inputs  
↓  
233 Payroll Note Inputs  
↓  
Payroll Note Automation Prototype

## Implementation

- Log processing and segmentation: C++
- Dataset B analysis: C++
- Automation prototype: Python + Playwright

## Prototype

The prototype demonstrates automated filling of the observed payroll note field (`#pi-note`) using browser DOM automation.

The production payroll application was not available locally, so the prototype was validated against a local reproduction of the observed field.

## How to Run the Prototype

```bash
pip install playwright
python -m playwright install
python prototype/payroll_note.py