# Performance issues 

Here are some noticable performance issues detected (till now) - 

## 1. Networking on the same thread 

Networking is NOT done via a different thread. Its done on the same thread as the program is running. Open a PR to resolve this issue if you know. (Issue reported by noerlol (<@noerlol> on discord). Thanks!) 

## 2. It might take some time 

Be patient. A single query can take upto 5 seconds to respond, and an article to some 6-7 seconds. (that 6-7 isnt intentional btw, newgens). 

**Why?** - 

The reason this is happening because programs can suck. Even something as the WINNT kernel isnt perfect. 

As the reason to tpedia, just understand by this short rough graph - 

User searches for smth -> Client sends GET Request to the server -> The server respond with a JSON -> nlohmann/json and FTXUI to parse the JSON 

Now if a user clicks on article (this is a process with much length), the following steps are involved - 

Client sends GET request to server for that specific article -> Server respond with HTML (this is important) -> Client, with that exact wikitext, sends a POST request to the server for converting that HTML to Wikitext -> Server responds with wikitext -> Client then to clean that wikitext -> Client shows that wikitext to end-user

All these takes up much time than requested. If only wikipedia had a direct wikitext GET request, then that would not be a problem. BARE WITH IT!!

> Please make a program to convert wikitext into markdown 