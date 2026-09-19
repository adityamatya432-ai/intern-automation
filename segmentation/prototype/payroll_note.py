from playwright.sync_api import sync_playwright

note = input("Enter payroll note: ")

with sync_playwright() as p:
    browser = p.chromium.launch(channel="msedge", headless=False)
    page = browser.new_page()

    page.set_content('<textarea id="pi-note"></textarea>')

    page.locator("#pi-note").fill(note)

    if page.locator("#pi-note").input_value() == note:
        print("SUCCESS: Payroll note filled")
    else:
        print("FAILED")

    input("Press Enter to close...")
    browser.close()