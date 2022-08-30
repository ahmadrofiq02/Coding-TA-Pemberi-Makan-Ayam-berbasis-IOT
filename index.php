<!doctype html>
<html lang="en">
  <head>
    <!-- Required meta tags -->
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">

    <!-- Bootstrap CSS -->
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css" integrity="sha384-Gn5384xqQ1aoWXA+058RXPxPg6fy4IWvTNh0E263XmFcJlSAwiGgFAW/dAiS6JXm" crossorigin="anonymous">
    <link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
    <link href="https://fonts.googleapis.com/css2?family=Outfit:wght@100;200;300;400;500;600;700;800;900&display=swap" rel="stylesheet">
    <link rel="stylesheet" href="style.css">
    <title>Kontrol Makan Ayam Otomatis</title>
  </head>
  <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.6.0/jquery.min.js"></script>
  <script>
    $(document).ready(function(){
      setInterval(function(){
        $("#keterangantempatmakan").load('keterangantempatmakan.php')
        $("#keterangankipas").load('keterangankipas.php')
        $("#keteranganlampu").load('keteranganlampu.php')
      },1000);
    });
  </script>
  <body>
    <nav class="navbar navbar-expand-lg navbar-light bg-light">
        <a class="navbar-brand" href="index,php">Kontrol Makan Ayam</a>
        <button class="navbar-toggler" type="button" data-toggle="collapse" data-target="#navbarNav" aria-controls="navbarNav" aria-expanded="false" aria-label="Toggle navigation">
          <span class="navbar-toggler-icon"></span>
        </button>
        <div class="collapse navbar-collapse" id="navbarNav">
          <ul class="navbar-nav ml-auto">
            <li class="nav-item active">
              <a class="nav-link" href="index.php">Home <span class="sr-only">(current)</span></a>
            </li>
            <li class="nav-item">
              <a class="nav-link" href="aturwaktu.php">Atur Jadwal Makan Ayam</a>
            </li>
            <li class="nav-item">
              <a class="nav-link" href="#">Data Jadwal Makan Ayam</a>
            </li>
          </ul>
        </div>
      </nav>
      <div class="row my-3 d-flex justify-content-center align-items-center">
          <h3>
              Kontrol Tempat Makanan Ayam
          </h3>
      </div>
      <div class="row my-4 d-flex justify-content-center align-items-center">
          <div class="col-lg-2 d-flex justify-content-center align-items-center">
              <a href="kirimservo.php?nilaiservo=1" class="btn btn-primary px-4 py-2 my-2">Buka Tempat Makanan</a>
          </div>
          <div class="col-lg-2 d-flex justify-content-center align-items-center">
              <a href="kirimservo.php?nilaiservo=0" class="btn btn-danger px-4 py-2 my-2">Tutup Tempat Makanan</a>
          </div>
      </div>
      <div class="row my-3 d-flex justify-content-center align-items-center">
          <div class="col-lg-2 d-flex justify-content-center align-items-center">
              <h5>Keterangan : </h5>
          </div>
          <div class="col-lg-3 d-flex justify-content-center align-items-center">
              <div id="keterangantempatmakan"></div>
          </div>
    </div>
    <div class="row my-3 d-flex justify-content-center align-items-center">
          <h3>
              Kontrol Kipas
          </h3>
      </div>
    <div class="row my-4 d-flex justify-content-center align-items-center">
        <div class="col-lg-2 d-flex justify-content-center align-items-center">
            <a href="kirimrelay.php?nilairelay=1" class="btn btn-primary px-4 py-2 my-2">Hidupkan Kipas</a>
        </div>
        <div class="col-lg-2 d-flex justify-content-center align-items-center">
            <a href="kirimrelay.php?nilairelay=0" class="btn btn-danger px-4 py-2 my-2">Matikan Kipas</a>
        </div>
    </div>
    <div class="row my-3 d-flex justify-content-center align-items-center">
          <div class="col-lg-2 d-flex justify-content-center align-items-center">
              <h5>Keterangan : </h5>
          </div>
          <div class="col-lg-2 d-flex justify-content-center align-items-center">
              <div id="keterangankipas"></div>
          </div>
    </div>
    <div class="row my-3 d-flex justify-content-center align-items-center">
        <h3>
            Kontrol Lampu
        </h3>
    </div>
    <div class="row my-4 d-flex justify-content-center align-items-center">
        <div class="col-lg-2 d-flex justify-content-center align-items-center">
            <a href="kirimrelay1.php?nilairelay=1" class="btn btn-primary px-4 py-2 my-2">Hidupkan Lampu</a>
        </div>
        <div class="col-lg-2 d-flex justify-content-center align-items-center">
            <a href="kirimrelay1.php?nilairelay=0" class="btn btn-danger px-4 py-2 my-2">Matikan Lampu</a>
        </div>
    </div>
    <div class="row my-3 d-flex justify-content-center align-items-center">
          <div class="col-lg-2 d-flex justify-content-center align-items-center">
              <h5>Keterangan : </h5>
          </div>
          <div class="col-lg-2 d-flex justify-content-center align-items-center">
              <div id="keteranganlampu"></div>
          </div>
    </div>
    
    <!-- Optional JavaScript -->
    <!-- jQuery first, then Popper.js, then Bootstrap JS -->
    </body>
</html>