\name{sftpDownload}
\alias{sftpDownload}
\title{
sftpDownload
}
\description{
Downloads a file from an ftp server.
}
\usage{
sftpDownload(host, username, password, remotepath, localpath)
}
\details{
Downloads a file from an ftp server.
}
\value{
TODO
}
\references{
www.libssh2.org
}
\author{
Bruce Hoff <bruce.hoff@sagebase.org>
}
\note{
The underlying C code supports public key authentication but this version of Rssh2 supports only username+password authentication.
}

\seealso{
sftpUpload
}
\examples{
\dontrun{
sftpDownload("sftp.server.org", "username", "password", "/path/to/dest/remotefile.txt", "/source/location/localfile.txt")
}
}

