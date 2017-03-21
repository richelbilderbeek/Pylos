#ifndef PYLOSMENUDIALOG_H
#define PYLOSMENUDIALOG_H

#include "menudialog.h"

namespace ribi {
namespace pylos {

///PylosMenuDialog contains the Pylos menu dialog
struct MenuDialog final : public ::ribi::MenuDialog
{
  MenuDialog() noexcept;
  About GetAbout() const noexcept override;
  Help GetHelp() const noexcept override;
  std::string GetVersion() const noexcept override;
  std::vector<std::string> GetVersionHistory() const noexcept override;

  private:
  int ExecuteSpecific(const std::vector<std::string>& argv) noexcept override;
};

} //~namespace pylos
} //~namespace ribi

#endif // PYLOSMENUDIALOG_H
