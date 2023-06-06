<a name="readme-top"></a>

# ChessGame

<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li><a href="#about-the-project">About The Project</a></li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#running-the-program">Running the Program</a></li>
      </ul>
    </li>
    <li><a href="#sample-output">Sample Output</a></li>
    <li><a href="#contact">Contact</a></li>
    <li><a href="#acknowledgments">Acknowledgments</a></li>
  </ol>
</details>


<!-- ABOUT THE PROJECT -->
## About The Project

![Product Name Screen Shot][product-screenshot]

This is a tool built to analyse if a set of chess move is valid with logic checks implemented.
It is able to check:
1. If it's black or white's turn currently.
2. If the move is valid basic move based on the current chess piece type.
3. If the move is a castling move.
4. If a move will leave itself in check.
5. If a move will result to a check or checkmate.
<p align="right">(<a href="#readme-top">back to top</a>)</p>


<!-- GETTING STARTED -->
## Getting Started

### Prerequisites

All you need is a compiler that is able to compile c++ program. :)

### Running the program

1. Clone the repo
   ```sh
   git clone https://github.com/liangsiwei1994/ChessGame.git
   ```
2. Open the `ChessMain.cpp` file.
3. Initialize an empty chessboard using
   ```sh
   ChessBoard cb;
   ```
   represents moving the chess piece in position E2 to E4.
4. Type in the set of moves using the following line into the `ChessMain.cpp` file, where the first move is in the first line, the last move is in the last line.
   ```sh
   cb.submitMove("E2", "E4");
   ```
   represents moving the chess piece in position E2 to E4.
5. To reset the board for a new set of moves to be analyzed within a single compilation, use:
   ```js
   cb.resetBoard();
   ```
   where cb is the instance of chessboard created.
6. Open the terminal. Go to the folder/directory path and compile the program using the following command
   ```js
   make
   ```
7. In the same path, run the program using
   ```js
   ./chess
   ```

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- SAMPLE OUTPUT -->
## Sample Output

The following image shows the expected output based on the current ChessMain.cpp file.

![Sample Output Screenshot][sampleoutput-screenshot]

<p align="right">(<a href="#readme-top">back to top</a>)</p>


<!-- CONTACT -->
## Contact

SiWei - liang_siwei@hotmail.com

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- ACKNOWLEDGMENTS -->
## Acknowledgments

Use this space to list resources you find helpful and would like to give credit to. I've included a few of my favorites to kick things off!

* [Professor William Knottenbelt](https://www.imperial.ac.uk/people/w.knottenbelt)
* Tom Crossland - t.crossland22@imperial.ac.uk
* [vi-dev0](https://github.com/othneildrew/Best-README-Template.git)

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- MARKDOWN LINKS & IMAGES -->
[product-screenshot]: images/ChessBoardImage.png
[sampleoutput-screenshot]: images/SampleOutput.png
