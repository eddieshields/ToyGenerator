# Hackathon

To measure mixing go to the directory ```/eos/user/e/eshields/Analysis/branches/fitting/d02kskk-ycp```.

Then,

```bash
. setup.sh
cd D02KSKKAnalysis
```

Open a pyhton virtual environment and

```bash
pip install tqdm
```

To measure mixing in the toy,

```bash
python3 macros/measurement-toy.py -i <path/to/toy> -toy 0
```

The result is saved to,

```bash
/eos/user/e/eshields/Analysis/branches/fitting/d02kskk-ycp/D02KSKKAnalysis/res/toymeasurement/Generator/ratio_toy0.root
```
