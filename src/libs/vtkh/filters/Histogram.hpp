#ifndef VTK_H_HISTOGRAM_HPP
#define VTK_H_HISTOGRAM_HPP

#include <vtkh/vtkh.hpp>
#include <vtkh/vtkh_exports.h>
#include <vtkh/filters/Filter.hpp>
#include <vtkh/DataSet.hpp>

#include <vector>
#include <iostream>

namespace vtkh
{

class VTKH_API Histogram : public Filter
{
public:
  Histogram();
  virtual ~Histogram();

  struct HistogramResult
  {
    vtkm::cont::ArrayHandle<vtkm::Id> m_bins;
    vtkm::Range m_range;
    vtkm::Float64 m_bin_delta;
    void Print(std::ostream &out);
    vtkm::Id totalCount();
  };

  //Keep for HistSampling until new VTKM filter   
  HistogramResult Run(vtkh::DataSet &data_set, const std::string &field_name);
  HistogramResult
  merge_histograms(std::vector<Histogram::HistogramResult> &histograms);

  std::string GetName() const override;
  void SetRange(const vtkm::Range &range);
  void SetNumBins(const int num_bins);
protected:
  void PreExecute() override;
  void PostExecute() override;
  void DoExecute() override;
  std::string m_field_name; 
  int m_num_bins;
  vtkm::Range m_range;
};

} //namespace vtkh
#endif
