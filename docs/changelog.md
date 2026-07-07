
# Changelog for tpedia 

> [!NOTE]
> Starting from v1.0.1-alpha-1. This would not track changes before v1.0.0 and its beta releases. 

# v1.1.0-alpha-1 

- Added a "Please wait for a few mooments" Screen. 
- Removed dependencies - matjson (hence geode-sdk/result)
- Added dependencies - nlohmann/json 

### Networking Change 
- Networking on a different thread (thanks for noerlol for that). 
- May possibly change for an async library (maybe Boost.Asio. If thats the case, then i will change json dependency to Boost.JSON) 
- Very big change...

### Why nlohmann/json? 

The idea of matjson seems reasonable first, a complete library with dumping things, simmilar to the function of Matjson. 
However, i do feel like that Matjson is not the library for a polished Thing like tpedia. Also the idea of geode-sdk/result
is not used elsewhere except matjson.

Its not like i disrespect Matjson; I will use it whenever i feel its appropriate. As for the result library, i dont wanna give 
opinion on that. 

Many people have suggested me to use an industry-ready nlohmann/json and compared to matjson, i feel like matjson isnt updated over
time. (The last commit was 3 months ago. It rarely recieves commits). So, a community built project is suitable for my library. 

---

Thanks! See you in v1.0.1-alpha-2! 
