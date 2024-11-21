# Bridge_Vibration_Analysis

Questo repository contiene i file e i documenti relativi al progetto di analisi delle vibrazioni di un modello in scala di un ponte. Il progetto è stato ideato per studiare i fenomeni di cedimento strutturale e vibrazioni sismiche, utilizzando sensori inerziali e un'applicazione per la raccolta e analisi dei dati. Condivido questo materiale per rendere il progetto replicabile e utile ad altri ricercatori, studenti e appassionati.

## Descrizione del progetto

Il progetto si basa su un modello in scala di un ponte progettato per simulare due scenari distinti:
1. L'abbassamento di uno o più piloni.
2. Vibrazioni indotte da terremoti.

### Struttura del repository

La repository è organizzata come segue:

- **/docs**: Contiene i documenti di riferimento che spiegano la teoria utilizzata per trasformare i dati dei sensori inerziali in angoli di rollio (roll), beccheggio (pitch) e imbardata (yaw). I documenti disponibili sono:
  - `Raccolta dati da smartphone.docx`: Spiega come raccogliere i dati dai sensori del telefono.
  - `Stima orientamento di un corpo.docx`: Illustra la teoria della stima dell'orientamento.

- **/viadotto**: Contiene i file specifici del modello in scala, suddivisi in sottocartelle:
  - **/codice_arduino**: Include il file `codice_arduino.ino`, fondamentale per il controllo del modello. In questo file sono presenti le variabili che consentono di regolare:
    - **L'abbassamento dei piloni**: *minVertical, maxVertical*.
    - **L'intensità del terremoto**: *minHorizontal, maxHorizontal*.
  - **/immagini e video**: File multimediali che mostrano il modello in funzione.
  - **/modelli 3D**: Contiene i file progettati con SketchUp:
    - `viadotto.skp`: Il modello 3D del ponte.
    - `viadotto abbassato.skp`: Una previsione del comportamento del ponte durante il cedimento di un pilone.
  - **/schema elettrico**: Include lo schema elettrico necessario per replicare il sistema:
    - `Schema elettrico ponte.dwg`
    - `Schema elettrico ponte.pdf`

- **Tesi Riccardo Florio.pdf**: La tesi completa, che documenta ogni aspetto del progetto.

## Obiettivi del progetto

Questo lavoro mira a fornire un sistema replicabile per analizzare le vibrazioni strutturali utilizzando un modello in scala di un ponte. La teoria utilizzata è ben documentata nei file contenuti in `/docs`, mentre le cartelle `/modelli 3D` e `/schema elettrico` offrono tutti i dettagli necessari per costruire il modello fisico. Il file `codice_arduino.ino` consente di controllare i fenomeni simulati, regolando con precisione l'abbassamento dei piloni e l'intensità delle vibrazioni.

## Come usare questo materiale

1. **Studio della teoria**: Inizia leggendo i documenti in `/docs` per comprendere come i dati dei sensori inerziali vengono trasformati in roll, pitch e yaw.
2. **Costruzione del modello**: Usa i file in `/modelli 3D` e `/schema elettrico` per costruire il modello in scala e configurare il sistema elettronico.
3. **Programmazione del modello**: Carica il file `codice_arduino.ino` sulla scheda Arduino Uno e regola le variabili per adattare il comportamento del modello alle tue esigenze.
4. **Simulazione**: Utilizza il modello per simulare scenari di cedimento strutturale e vibrazioni sismiche, raccogliendo dati per analisi successive.

## Licenza

Il materiale condiviso in questa repository è rilasciato con una licenza open-source, consentendo a chiunque di utilizzare, modificare e distribuire i contenuti, con l'obiettivo di promuovere la collaborazione e la condivisione della conoscenza.