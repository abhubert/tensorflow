# tensorflow (development version)

# tensorflow 2.7.0

- Default Tensorflow version installed by `install_tensorflow()` updated to 2.7

- Breaking changes:
  - `shape()` now returns a `tf.TensorShape()` object
    (Previously an R-list of `NULL`s or integers).
  - `[` method for `tf.TensorShape()` objects also now returns a `tf.TensorShape()`.
    Use `[[`, `as.numeric`, `as.integer`, and/or `as.list` to convert to R objects.
  - `length()` method for `tensorflow.tensor` now returns `NA_integer_` for
    tensors with not fully defined shapes. (previously a zero length integer vector).
  - `dim()` method for `tensorflow.tensor` now returns an R integer vector
    with `NA` for dimensions that are undefined.
    (previously an R list with `NULL` for undefined dimension)

- New S3 generics for `tf.TensorShape()`'s:
  `c`, `length`, `[<-`, `[[<-`, `merge`, `==`, `!=`, `as_tensor()`,
  `as.list`, `as.integer`, `as.numeric`, `as.double`, `py_str`
  (joining previous generics `[` and `[[`).
  See `?shape` for extended examples.

- Ops S3 generics for `tensorflow.tensor`s that take two arguments now
  automatically cast a supplied non-tensor to the dtype of the supplied tensor
  that triggered the S3 dispatch. Casting is done via `as_tensor()`.
  e.g., this now works:
    ```
    as_tensor(5L) - 2     # now returns tf.Tensor(3, shape=(), dtype=int32)
    ```
  previously it would raise an error:
    ```
    TypeError: `x` and `y` must have the same dtype, got tf.int32 != tf.float32
    ```
  Generics that now do autocasting:
    +, -, *, /, %/%, %%, ^, &, |, ==, !=, <, <=, >, >=

- `install_tensorflow()`: new argument with default `pip_ignore_installed = TRUE`. 
  This ensures that all Tensorflow dependencies like Numpy are installed by pip 
  rather than conda.

- A message with the Tensorflow version is now shown when the
  python module is loaded, e.g: "Loaded Tensorflow version 2.6.0"

# tensorflow 2.6.0

- Updated default Tensorflow version to 2.6.

- Changed default in `tf_function()` to `autograph=TRUE`.

- Added S3 generic `as_tensor()`.

- tfautograph added to Imports

- jsonlite removed from Imports, tfestimators removed from Suggests

- Refactored `install_tensorflow()`.
  - Potentially breaking change: numeric versions supplied without a patchlevel now automatically pull the latest patch release.
    (e.g. `install_tensorflow(version="2.4")` will install `"2.4.2"`. Previously it would install "2.4.0")

- Removed "Config/reticulate" declaration from DESCRIPTION.
  - Setting `RETICULATE_AUTOCONFIGURE=FALSE` environment variable when using non-default tensorflow installations (e.g., 'tensorflow-cpu') no longer required.
  - Users will have to call `install_tensorflow()` for automatic installation.

- Refactored automated tests to closer match the default installation procedure
  and compute environment of most user.

- Expanded CI test coverage to include R devel, oldrel and 3.6.

- Fixed an issue where extra packages with version constraints like
  `install_tensorflow(extra_packages = "Pillow<8.3")` were not quoted properly.

- Fixed an issue where valid tensor-like objects supplied to
  `log(x, base)`, `cospi()`, `tanpi()`, and `sinpi()` would raise an error.


# tensorflow 2.5.0

- Updated default Tensorflow version to 2.5.
- Added support for additional arguments in `tf_function()` (e.g., `jit_compile`)
- Added support for `expm1` S3 generic.
- `tfe_enable_eager_execution` is deprecated. Eager mode has been the default since TF version 2.0.
- Improved error message in `tf_config()` on unsuccessful installation.

# tensorflow 2.4.0

- Fixed error with `use_session_with_seed` (#428)
- Added a new `set_random_seed` function that makes more sense for TensorFlow >= 2.0 (#442)
- Updated the default version of TensorFlow to 2.4 as well as the default Python to 3.7 (#454)

# TensorFlow 2.2.0 (CRAN)

- Bugfix with `all_dims` (#398)

- Indexing for TensorShape & `py_to_r` conversion (#379, #388)

# TensorFlow 2.0.0 (CRAN)

- Upgraded default installed version to 2.0.0.

- Tensorboard log directory path fixes (#360).

- Allow for `v1` and `v2` compat (#358).

- `install_tensorflow` now does not installs `tfprobability`, `tfhub` and other
 related packages.

# TensorFlow 1.14.1 (CRAN)

- Upgraded default installed version to 1.14.0

- Refactored the `install_tensorflow` code delegating to `reticulate` (#333, #341): We completely delegate to installation to `reticulate::py_install`, the main difference is that now the default environment name to install is `r-reticulate` and not `r-tensorflow`.

# TensorFlow 1.13.1 (CRAN)

- added option to silence TF CPP info output

- `tf_gpu_configured` function to check if GPU was correctly
