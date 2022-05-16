<!DOCTYPE html>
<!-- saved from url=(0141)file:///C:/Users/mpran/Documents/GitHub/MolecularDynamicsSimulation/docs/Welcome%20to%20GitHub%20Pages%20_%20MolecularDynamicsSimulation.html -->
<html lang="en-US"><head><meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
    
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1">
    <link rel="stylesheet" href="./index_files/style.css" media="screen" type="text/css">
    <link rel="stylesheet" href="./index_files/print.css" media="print" type="text/css">

    <!--[if lt IE 9]>
    <script src="https://oss.maxcdn.com/html5shiv/3.7.3/html5shiv.min.js"></script>
    <![endif]-->

<!-- Begin Jekyll SEO tag v2.8.0 -->
<title>Molecular Dynamics Simulation</title>
<meta name="generator" content="Jekyll v3.9.2">
<meta property="og:title" content="Molecular Dynamics Simulation">
<meta property="og:locale" content="en_US">
<meta name="description" content="2D Molecular Dynamics Simulation">
<meta property="og:description" content="2D Molecular Dynamics Simulation using Leonard Jones">
<link rel="canonical" href="https://pm623.github.io/MolecularDynamicsSimulation/">
<meta property="og:url" content="https://pm623.github.io/MolecularDynamicsSimulation/">
<meta property="og:site_name" content="MolecularDynamicsSimulation">
<meta property="og:type" content="website">
<meta name="twitter:card" content="summary">
<meta property="twitter:title" content="Molecular Dynamics Simulation">
<script type="application/ld+json">
{"@context":"https://schema.org","@type":"WebSite","description":"2D Molecular Dynamics Simulation","headline":"Welcome to GitHub Pages","name":"MolecularDynamicsSimulation","url":"https://pm623.github.io/MolecularDynamicsSimulation/"}</script>
<!-- End Jekyll SEO tag -->


    <!-- start custom head snippets, customize with your own _includes/head-custom.html file -->

<!-- Setup Google Analytics -->



<!-- You can set your favicon here -->
<!-- link rel="shortcut icon" type="image/x-icon" href="/MolecularDynamicsSimulation/favicon.ico" -->

<!-- end custom head snippets -->

  </head>

  <body>
    <header>
      <div class="inner">
        <a href="https://pm623.github.io/MolecularDynamicsSimulation/">
          <h1>MD Simulation</h1>
        </a>
        <h2>2D Molecular Dynamics Simulation </h2>
        
          <a href="https://github.com/pm623/MolecularDynamicsSimulation" class="button"><small>View project on</small> GitHub</a>
        
        
      </div>
    </header>

    <div id="content-wrapper">
      <div class="inner clearfix">
        <section id="main-content">
          <h2 id="welcome-to-github-pages">Introduction</h2>

<p>An Altera System-on-Chip FPGA with an integrated ARM hard processor system (HPS) was used as the development platform to perform a 2D molecular dynamics simulation of symmetrical, inert atoms.
   Molecular interaction was visualized on a VGA display with molecules represented as circles interacting with each other and changing colors corresponding to the amount of energy each molecule had.
    The visualizer worked in tandem with a C program running on the HPS to allow for user input to control the simulation from the command line, as well as a USB mouse.
     Memory manipulation via the Qsys bus allowed for configurable communication between the HPS and the FPGA as data was passed to the FPGA from the ARM, and vice-versa.
      Correctness of the system was continuously verified throughout development by analyzing waveforms in ModelSim, using the onboard LEDs and visualizing the output on the VGA Monitor.
       The objective was to efficiently utilize the resources on the FPGA to be able to visualize molecular interaction on a reasonable timescale.
</p>


<h2 id="welcome-to-github-pages">Demo</h2>

<iframe width="560" height="315" src="https://www.youtube.com/embed/mpDcrlHr-kI" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>



<h2 id="markdown">Motivation</h2>

<p>Molecular dynamics is a notoriously computationally-expensive Newtonian modeling technique that has applications in everything from materials research to biochemistry. Given its complexity, acceleration of the simulation is an area that’s given significant research attention today. For our final project, we wanted to implement a 2D molecular dynamics simulation of a liquid that exhibits a phase change to a gas when a user adds energy to a system and vice-versa, in order to explore the viability of molecular dynamics simulations on an FPGA. Specifically, we want to observe phase changes when energy is added or removed from the system in the form of condensation/evaporation or crystallization/melting. Even though accurate molecular simulations require consideration of all 3-dimensions, we believe that creating a 2D version of the simulation can inform further efforts at accelerating the full 3-dimensional simulations.
</p>

<p>Markdown is a lightweight and easy-to-use syntax for styling your writing. It includes conventions for</p>

<div class="language-markdown highlighter-rouge"><div class="highlight"><pre class="highlight"><code>Syntax highlighted code block

<span class="gh"># Header 1</span>
<span class="gu">## Header 2</span>
<span class="gu">### Header 3</span>
<span class="p">
-</span> Bulleted
<span class="p">-</span> List
<span class="p">
1.</span> Numbered
<span class="p">2.</span> List

<span class="gs">**Bold**</span> and _Italic_ and <span class="sb">`Code`</span> text

<span class="p">[</span><span class="nv">Link</span><span class="p">](</span><span class="sx">url</span><span class="p">)</span> and !<span class="p">[</span><span class="nv">Image</span><span class="p">](</span><span class="sx">src</span><span class="p">)</span>
</code></pre></div></div>

<p>For more details see <a href="https://docs.github.com/en/github/writing-on-github/getting-started-with-writing-and-formatting-on-github/basic-writing-and-formatting-syntax">Basic writing and formatting syntax</a>.</p>

<h3 id="jekyll-themes">Jekyll Themes</h3>

<p>Your Pages site will use the layout and styles from the Jekyll theme you have selected in your <a href="https://github.com/pm623/MolecularDynamicsSimulation/settings/pages">repository settings</a>. The name of this theme is saved in the Jekyll <code class="language-plaintext highlighter-rouge">_config.yml</code> configuration file.</p>

<h3 id="support-or-contact">Support or Contact</h3>

<p>Having trouble with Pages? Check out our <a href="https://docs.github.com/categories/github-pages-basics/">documentation</a> or <a href="https://support.github.com/contact">contact support</a> and we’ll help you sort it out.</p>

        </section>

        <aside id="sidebar">
          

          
            <p class="repo-owner"><a href="https://github.com/pm623/MolecularDynamicsSimulation">MolecularDynamicsSimulation</a> is maintained by <a href="https://github.com/pm623">pm623</a>.</p>
          

          <p>This page was generated by <a href="https://pages.github.com/">GitHub Pages</a>.</p>
        </aside>
      </div>
    </div>

  

</body></html>