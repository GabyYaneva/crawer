C-Based Web Crawler
A high-performance, low-level Web Crawler implemented in C. This tool traverses the web by fetching HTML content and recursively extracting links to discover new pages. It combines network programming with string parsing logic to map out web structures.

🕸️ How it Works
The crawler operates in a loop, following these fundamental steps:

Seed URL: Starts with a base URL provided by the user.

Fetch: Uses a custom socket-based engine (similar to an HTTP client) to download the HTML.

Parse: Scans the raw HTML buffer for href attributes and extract links.

Filter & Queue: Validates the discovered URLs and adds them to a processing queue.

Repeat: Continues the process until a depth limit or a specific number of pages is reached.

🛠️ Key Features
Custom HTTP Engine: Built on top of POSIX sockets for raw data retrieval.

HTML Parsing: Manual string manipulation and pattern matching to identify links within <a> tags.

Recursion Control: Logic to prevent infinite loops and limit crawling depth.

Memory Management: Efficient buffer handling for processing large HTML responses.

String Parsing in C: Implementing robust logic to find links without the help of regex or heavy HTML libraries.

Network Timeouts: Managing socket connections that might hang or fail.

📊 Potential Use Cases
SEO Analysis: Checking for broken links on a website.

Site Mapping: Creating a visual map of a site's structure.

Data Mining: Gathering specific information from a targeted domain.

⚠️ Disclaimer
This project is for educational purposes. Please be mindful of robots.txt files and avoid overloading servers (aggressive crawling) when testing.
