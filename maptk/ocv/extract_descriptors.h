/*ckwg +29
 * Copyright 2013-2014 by Kitware, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *  * Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 *  * Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 *  * Neither name of Kitware, Inc. nor the names of any contributors may be used
 *    to endorse or promote products derived from this software without specific
 *    prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHORS OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * \file
 * \brief MAPTK algorithm wrapping of OCV's DescriptorExtractor
 */

#ifndef MAPTK_OCV_EXTRACT_DESCRIPTORS_H_
#define MAPTK_OCV_EXTRACT_DESCRIPTORS_H_

#include "ocv_config.h"
#include <maptk/core/algo/extract_descriptors.h>

#include <boost/scoped_ptr.hpp>

namespace maptk
{

namespace ocv
{

/// An class for extracting feature descriptors using OpenCV
class MAPTK_OCV_EXPORT extract_descriptors
  : public algo::algorithm_impl<extract_descriptors, algo::extract_descriptors>
{
public:
  /// Default Constructor
  extract_descriptors();

  /// Destructor
  virtual ~extract_descriptors();

  /// Copy Constructor
  extract_descriptors(const extract_descriptors& other);

  /// Return the name of this implementation
  std::string impl_name() const { return "ocv"; }

  /// Get this algorithm's \link maptk::config_block configuration block \endlink
  virtual config_block_sptr get_configuration() const;
  /// Set this algorithm's properties via a config block
  virtual void set_configuration(config_block_sptr config);
  /// Check that the algorithm's configuration config_block is valid
  virtual bool check_configuration(config_block_sptr config) const;

  /// Extract from the image a descriptor corresoponding to each feature
  /**
   * \param image_data contains the image data to process
   * \param features the feature locations at which descriptors are extracted
   * \returns a set of feature descriptors
   */
  virtual descriptor_set_sptr
  extract(image_container_sptr image_data,
          feature_set_sptr features) const;

private:
  /// private implementation class
  class priv;
  boost::scoped_ptr<priv> d_;
};

} // end namespace ocv

} // end namespace maptk


#endif // MAPTK_OCV_EXTRACT_DESCRIPTORS_H_
