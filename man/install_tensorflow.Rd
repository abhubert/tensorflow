% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/install.R
\name{install_tensorflow}
\alias{install_tensorflow}
\title{Install TensorFlow and its dependencies}
\usage{
install_tensorflow(
  method = c("auto", "virtualenv", "conda"),
  conda = "auto",
  version = "default",
  envname = NULL,
  extra_packages = NULL,
  restart_session = TRUE,
  conda_python_version = "3.7",
  ...,
  pip_ignore_installed = TRUE,
  python_version = conda_python_version
)
}
\arguments{
\item{method}{Installation method. By default, "auto" automatically finds a
method that will work in the local environment. Change the default to force
a specific installation method. Note that the "virtualenv" method is not
available on Windows.}

\item{conda}{The path to a \code{conda} executable. Use \code{"auto"} to allow
\code{reticulate} to automatically find an appropriate \code{conda} binary. See
\strong{Finding Conda} for more details.}

\item{version}{TensorFlow version to install. Valid values include:
\itemize{
\item \code{"default"} installs  2.7
\item \code{"release"} installs the latest release version of tensorflow (which may
be incompatible with the current version of the R package)
\item A version specification like \code{"2.4"} or \code{"2.4.0"}. Note that if the patch
version is not supplied, the latest patch release is installed (e.g.,
\code{"2.4"} today installs version "2.4.2")
\item \code{nightly} for the latest available nightly build.
\item To any specification, you can append "-cpu" to install the cpu version
only of the package (e.g., \code{"2.4-cpu"})
\item The full URL or path to a installer binary or python *.whl file.
}}

\item{envname}{The name, or full path, of the environment in which Python
packages are to be installed. When \code{NULL} (the default), the active
environment as set by the \code{RETICULATE_PYTHON_ENV} variable will be used;
if that is unset, then the \code{r-reticulate} environment will be used.}

\item{extra_packages}{Additional Python packages to install along with
TensorFlow.}

\item{restart_session}{Restart R session after installing (note this will
only occur within RStudio).}

\item{...}{other arguments passed to \code{\link[reticulate:conda-tools]{reticulate::conda_install()}} or
\code{\link[reticulate:virtualenv-tools]{reticulate::virtualenv_install()}}, depending on the \code{method} used.}

\item{pip_ignore_installed}{Whether pip should ignore installed python
packages and reinstall all already installed python packages. This defaults
to \code{TRUE}, to ensure that TensorFlow dependencies like NumPy are compatible
with the prebuilt TensorFlow binaries.}

\item{python_version, conda_python_version}{the python version installed in
the created conda environment. Ignored when attempting to install with a
Python virtual environment.}
}
\description{
\code{install_tensorflow()} installs just the tensorflow python package and it's
direct dependencies. For a more complete installation that includes
additional optional dependencies, use \code{\link[keras:install_keras]{keras::install_keras()}}.
}
\details{
You may be prompted you if you want it to download and install
miniconda if reticulate did not find a non-system installation of python.
Miniconda is the recommended installation method for most users, as it
ensures that the R python installation is isolated from other python
installations. All python packages will by default be installed into a
self-contained conda or venv environment named "r-reticulate". Note that
"conda" is the only supported method on Windows.

If you initially declined the miniconda installation prompt, you can later
manually install miniconda by running \code{\link[reticulate:install_miniconda]{reticulate::install_miniconda()}}.
}
\section{Custom Installation}{
 \code{install_tensorflow()} or
\code{keras::install_keras()} isn't required to use tensorflow with the package.
If you manually configure a python environment with the required
dependencies, you can tell R to use it by pointing reticulate at it,
commonly by setting an environment variable:

\code{Sys.setenv("RETICULATE_PYTHON" = "~/path/to/python-env/bin/python")}
}

\section{Apple Silicon}{
 Tensorflow on Apple Silicon is not officially
supported by the tensorflow maintainers. It is known that there can be
issues running the official Tensorflow package under Rosetta as well.
Fortunately, for the time being Apple has published a custom version of
Tensorflow compatible with M1 macs. Installation instructions can be found
at: \url{https://developer.apple.com/metal/tensorflow-plugin/}. Please note
that this is an experimental build of both python and tensorflow. After
following the instructions provided by Apple, you can advise reticulate to
use that python installation by placing the following in your \code{.Renviron}
file:

\code{RETICULATE_PYTHON = "~/miniforge3/bin/python"}
}

\section{Additional Packages}{


If you wish to add additional PyPI packages to your Keras / TensorFlow
environment you can either specify the packages in the \code{extra_packages}
argument of \code{install_tensorflow()} or \code{install_keras()}, or alternatively
install them into an existing environment using the
\code{\link[reticulate:py_install]{reticulate::py_install()}} function. Note that \code{install_keras()} includes a
set of additional python packages by default, see \code{?keras::install_keras}
for details.
}

\seealso{
\code{\link[keras:install_keras]{keras::install_keras()}}
}
